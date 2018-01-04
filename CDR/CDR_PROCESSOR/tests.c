#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "mu_test.h"
#include "storeSubData.h" 
#include "storeOptData.h"
#include "protocol.h"
#include "TransmissionData.h"
#include "../../inc/logger.h"
#include "../../inc/config.h"
#include "dealQuery.h"
#include "proccessorManagment.h"


#define CONF_FILE "Conf.txt"
#define PATH "/home/ido/Desktop/work/CDR/CDR_PROCESSOR"
#define KEY 'f'
#define TYPE 1
void PrintCdrRecord(CdrData* data)
{
	printf("opratorBrandName: %s | msidn: %s| m_type: %c| duration: %d | download: %d | upload: %d | tuple: %d: withinOperator: %c\n", data->m_opratorBrandName, data->m_msidn, data->m_type, data->m_duration, data->m_downloaded, data->m_uploaded, data->m_tuple, data->m_ParOprator);  
}


int openMessageQueue()
{
	int key, msqid;
	key = ftok(PATH, KEY);
	return msgget(key, 0666 | IPC_CREAT);
}	

CdrData** CdrCreate(int size)
{
    CdrData* *data;
    size_t i=0;
    char* msisdn[40] = {"12233456","234564567","34566778","45690789","12567890","67348901","78966012","7102270","90112234","01233445","18343456","14334567","34476678","456345789","567965490","60890661","789311012","71088970","901023141","011211345""12345116","23452367","34455678","45116789","56789230","67892201","78901212","7102170","90123433","0123423235","11183456","13451617","34412678","45612789","56791290","608901","789301212","71022870","9010234","0112893245"};

    char* namecom[10] ={"yaodav comm","shai comm","ido comm","nadav comm","eyal comm","erez comm","sarig comm","gal rita&yossi com","roy comm","hana comm"};
    
    char m_type[4] = {'a', 'b' , 'c', 'd'};

    data = malloc((size_t)size *sizeof(CdrData*));

    for (i = 0; i < size; i += 1)
    {
        data[i] = malloc(sizeof(CdrData));
        strcpy(data[i]->m_opratorBrandName, namecom[2]);
		strcpy(data[i]->m_msidn, msisdn[i%20]);
    	data[i]->m_type = m_type[i%4];  /*a = moc  b = mtc c = outgoing sms d = incoming sms e = web */
  		data[i]->m_duration = 10 +i;
  		data[i]->m_tuple = 12345 + (int)i;
		data[i]->m_downloaded = 10+ i;
		data[i]->m_uploaded = 1;
   		data[i]->m_ParOprator = m_type[i%2];
   		data[i]->m_ParOpratorTuple = size% (i+1);
    }
    return data;
}

void DestroyCDR(CdrData** _Cdr, int _size)
{
	size_t i;
	
	for(i = 0; i < _size; ++i)
	{
		free(_Cdr[i]);
	}
	free(_Cdr);
}

void InitQuery(Query* _query)
{
	strcpy(_query->m_subscriberMSISDN, "12345678901");
	strcpy(_query->m_path, "report.txt"); 
}



UNIT(CreateADTs)
    OperatorsADT* opt;
    SubscribersADT* sub;
    LogData*  LogD;
	LogD = GetLog(NULL);
	
    opt = CreateOperatorsADT(1500, LogD);
    sub = CreateSubscribersADT(1500, LogD); 
	ASSERT_THAT(NULL != opt); 
    ASSERT_THAT(NULL !=sub);
	DestroyOperatorsADT(opt);
    DestroySubscribersADT(sub); 
END_UNIT

UNIT(InsertADTs)
    OperatorsADT* opt;
    SubscribersADT* sub;
    CdrData** cdr;
    LogData*  LogD;
	LogD = GetLog(NULL);

    cdr = CdrCreate(1);
    
    opt = CreateOperatorsADT(1500, LogD); 
    sub = CreateSubscribersADT(1500, LogD);
	
	ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, cdr[0])); 
	ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, cdr[0])); 
	DestroyOperatorsADT(opt);
    DestroySubscribersADT(sub);
    DestroyCDR(cdr, 1);
END_UNIT

UNIT(InsertSameDataToADTs)
    OperatorsADT* opt;
    SubscribersADT* sub;
    CdrData data;
    LogData*  LogD;
	LogD = GetLog(NULL);
	
	strcpy(data.m_opratorBrandName, "cellcom");
	strcpy(data.m_msidn, "12345678912345");
    data.m_type = 'a';  /*a = moc  b = mtc c = outgoing sms d = incoming sms e = web  */ 
  	data.m_duration = 12;
	data.m_downloaded = 12;
	data.m_uploaded = 12;
	data.m_tuple = 12345;
   	data.m_ParOprator = 'a';  /*a = inside operator b = outside operator  */ 
    
    opt = CreateOperatorsADT(1500, LogD); 
    sub = CreateSubscribersADT(1500, LogD);
	ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, &data)); 
	ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, &data));
	ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, &data)); 
	ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, &data)); 
	DestroyOperatorsADT(opt);
    DestroySubscribersADT(sub);
END_UNIT

UNIT(InsertSameAndDiffrentDataToADTsMultipuleTimes)
    int i;
    OperatorsADT* opt;
    SubscribersADT* sub;
    CdrData** cdr;
    LogData*  LogD;
	LogD = GetLog(NULL);
	
    cdr = CdrCreate(10);
    opt = CreateOperatorsADT(1500, LogD);
    sub = CreateSubscribersADT(1500, LogD);
    
    for(i = 0; i < 1000; ++i)
    {
		ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, cdr[i%10])); 
		ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, cdr[i%10]));
    }
	DestroyOperatorsADT(opt);
    DestroySubscribersADT(sub);
    DestroyCDR(cdr, 10);
END_UNIT


UNIT(IsCreateandDestroyChannel)
	LogData*  LogD;
	LogD = GetLog(NULL);
    ASSERT_THAT(NULL != CreateTransmissionChannel(PATH , KEY, TYPE, LogD));
END_UNIT

UNIT(IsSendCDRMessage)
    ChannelData* channelData;
    CdrData** cdr;
    LogData*  LogD;
	LogD = GetLog(NULL);
    channelData = CreateTransmissionChannel(PATH , KEY, TYPE, LogD);
    ASSERT_THAT(channelData);

    cdr = CdrCreate(1); 
    ASSERT_THAT(0 ==PushToChannel((void*)cdr[0], sizeof(CdrData), channelData));
    DestroyChannel(channelData);
    DestroyCDR(cdr, 1);
END_UNIT

UNIT(IsGetCDRMessage)
    ChannelData* channelData;
    CdrData** cdr;
    CdrData data;
    LogData*  LogD;
	LogD = GetLog(NULL);
    channelData = CreateTransmissionChannel(PATH , KEY, TYPE, LogD);
    ASSERT_THAT(channelData);
    
    cdr = CdrCreate(1);
    
   	printf("feeder Cdr:");
   	PrintCdrRecord(cdr[0]);
    ASSERT_THAT(0 == PushToChannel((void*)cdr[0], sizeof(CdrData), channelData)); 
    while(ReadFromChannel((void*)&data, sizeof(CdrData), channelData) != -1)
    {
        printf("processor Cdr:");
	    PrintCdrRecord(&data);
    }
    DestroyChannel(channelData);

END_UNIT

UNIT(IsGetLastMessage)
    ChannelData* channelData;
    LogData*  LogD;
	LogD = GetLog(NULL);
    channelData = CreateTransmissionChannel(PATH , KEY, TYPE, LogD);
    ASSERT_THAT(channelData);
   	CdrData data; 
    
    ASSERT_THAT(0 == SendLastMessage(channelData));
    ASSERT_THAT(1 == ReadFromChannel((void*)&data, sizeof(CdrData), channelData));
    DestroyChannel(channelData);
END_UNIT

UNIT(IsPushAndGetNultipuleMessages)
    int i;
   ChannelData* channelData;
    CdrData** cdr;
    LogData*  LogD;
	LogD = GetLog(NULL);
    channelData = CreateTransmissionChannel(PATH , KEY, TYPE, LogD);
    ASSERT_THAT(channelData);
    
   	CdrData data; 
    cdr = CdrCreate(10);
    for(i = 0; i <10; ++i)
    {
   		ASSERT_THAT(0 == PushToChannel((void*)cdr[i%10], sizeof(CdrData), channelData));
   		ASSERT_THAT(0 == ReadFromChannel((void*)&data, sizeof(CdrData), channelData));
    } 
    DestroyChannel(channelData);
    DestroyCDR(cdr, 10);
END_UNIT

/*
UNIT(IsCreateUsingConfigFile)
    ASSERT_THAT(NULL != CreateTransmissionChannel(CONF_FILE));

END_UNIT
*/

UNIT(IsAnswerSubQuery)

    SubscribersADT* sub;
    CdrData** cdr;
    Query query;
    LogData*  LogD;
	LogD = GetLog(NULL);
    
    InitQuery(&query);
    cdr = CdrCreate(1);
    sub = CreateSubscribersADT(1500, LogD);
	
	ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, cdr[0])); 
	SubscriberQuery(sub, &query);

    DestroySubscribersADT(sub);
    DestroyCDR(cdr, 1);
END_UNIT

UNIT(IsAnswerSubQueryMultipuleSubscribers)
	
	size_t i;
    SubscribersADT* sub;
    CdrData** cdr;
    Query query;
    LogData*  LogD;
	LogD = GetLog(NULL);
	
    cdr = CdrCreate(100);
    sub = CreateSubscribersADT(1500, LogD);
    
    for(i = 0; i < 1000; ++i)
    {
		ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, cdr[i%100])); 
    }
    InitQuery(&query);

	SubscriberQuery(sub, &query);
    DestroySubscribersADT(sub);
    DestroyCDR(cdr, 1);
END_UNIT

UNIT(IsPrintSubscribersReportSubscribers)	
	size_t i;
    SubscribersADT* sub;
    CdrData** cdr;
    Query query;
    LogData*  LogD;
	LogD = GetLog(NULL);
	
    
    cdr = CdrCreate(100);
    sub = CreateSubscribersADT(1500, LogD);
    
    for(i = 0; i < 1000; ++i)
    {
		ASSERT_THAT(0 ==  InsertToSubscribersADT(sub, cdr[i%100])); 
    }
    InitQuery(&query);

	ASSERT_THAT(0 == AllSubscribersReport(sub, &query));
    DestroySubscribersADT(sub);
    DestroyCDR(cdr, 1);
END_UNIT

UNIT(IsAnswerOptQuery)
    OperatorsADT* opt;
    CdrData** cdr;
    Query query;
    LogData*  LogD;
    LogD = GetLog(NULL);
    
    InitQuery(&query);
    cdr = CdrCreate(1);
    opt = CreateOperatorsADT(1500, LogD);
	
	ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, cdr[0])); 
	OperatorQuery(opt, &query);

    DestroyOperatorsADT(opt);
    DestroyCDR(cdr, 1);
END_UNIT

UNIT(IsAnswerOptQueryMultipuleQueries)
    size_t i;
    OperatorsADT* opt;
    CdrData** cdr;
    Query query;
    LogData*  LogD;
    LogD = GetLog(NULL);
    
    InitQuery(&query);
    cdr = CdrCreate(100);
    opt = CreateOperatorsADT(1500, LogD);
	
	for(i = 0; i < 1000; ++i)
    {
		ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, cdr[i%100])); 
    }
    InitQuery(&query); 
	OperatorQuery(opt, &query);
    DestroyOperatorsADT(opt);
    DestroyCDR(cdr, 100);
END_UNIT

UNIT(IsPrintOperatorsReport)
    size_t i;
    OperatorsADT* opt;
    CdrData** cdr;
    Query query;
    LogData*  LogD;
    LogD = GetLog(NULL);
    
    InitQuery(&query);
    cdr = CdrCreate(100);
    opt = CreateOperatorsADT(1500, LogD);
	
	for(i = 0; i < 1000; ++i)
    {
		ASSERT_THAT(0 ==  InsertToOperatorsADT(opt, cdr[i%100])); 
    }
    InitQuery(&query); 
	ASSERT_THAT(0 == AllOperatorsReport(opt, &query));
    DestroyOperatorsADT(opt);
    DestroyCDR(cdr, 100);
END_UNIT

UNIT(IsCreateManager)
    LogData*  LogD;
    LogD = GetLog(NULL);
    ManagmentData* managmentData;
    ASSERT_THAT(CreateManagmentData(NULL));
END_UNIT


UNIT(IsReadAndInsert)
    ManagmentData* managmentData;
    CdrData data;
    LogData*  LogD;
    Query query;
    InitQuery(&query); 
    
	LogD = GetLog(NULL);
    managmentData = CreateManagmentData(NULL);
   	ProcessingRoutine(managmentData);
    ASSERT_THAT(0 == AllSubscribersReport(managmentData->m_subscribersADT, &query));
    ASSERT_THAT(0 == AllOperatorsReport(managmentData->m_operatorsADT, &query));
    DestroyManagmentData(managmentData);
     
END_UNIT

UNIT(Rotine)
	ManagerRoutine(NULL);
END_UNIT
	

TEST_SUITE(framework test)
	/*

	TEST(InsertADTs)
	TEST(InsertSameDataToADTs)
	TEST(InsertSameAndDiffrentDataToADTsMultipuleTimes)
	TEST(CreateADTs) 

	TEST(IsCreateandDestroyChannel)
	TEST(IsSendCDRMessage) 
	TEST(IsGetCDRMessage)
	
	TEST(IsGetLastMessage)
	TEST(IsPushAndGetNultipuleMessages)
	
	TEST(IsCreateUsingConfigFile)
	TEST(IsAnswerSubQuery)
	TEST(IsAnswerSubQueryMultipuleSubscribers)
	TEST(IsPrintSubscribersReportSubscribers)
	TEST(IsAnswerOptQuery)
	TEST(IsAnswerOptQueryMultipuleQueries)
	TEST(IsPrintOperatorsReport)
	
	TEST(IsCreateManager)

	TEST(IsReadAndInsert) 
	*/
	TEST(Rotine)
	
END_SUITE




