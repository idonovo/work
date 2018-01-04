#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>    

#include "interface.h"

/*TODO complete interface for main */ 

struct Input
{
	size_t m_numOfCycls, m_numOfProducers, m_numOfConsumers, m_queueSize;
};

struct CommunucationChannels
{
	Queue* m_qustionsQueue;
	Queue* m_answersQueue;
};

struct ParticipationsData
{
	Consumers*  m_consumers;
	Producers*  m_producers;
	void*       m_consumersContext;
	void*       m_producersContext;
};

/******************************************************************/
void ParseInput(Input* _input, int argc, char **argv)
{
	int c;

	_input->m_numOfCycls =  DEFAULT_SIZE;
	_input->m_numOfProducers =  DEFAULT_SIZE;
	_input->m_numOfConsumers =  DEFAULT_SIZE;
	_input->m_queueSize =  DEFAULT_SIZE;
	
	while ((c = getopt (argc, argv, "o: p: c: s:")) != -1)
	{
		switch (c)
		{
		case 'o':
			_input->m_numOfCycls = atoi(optarg);
			break;
		case 'p':
			_input->m_numOfProducers = atoi(optarg);
			break;
		case 'c':
			_input->m_numOfConsumers = atoi(optarg);
			break;
		case 's':
			_input->m_queueSize = atoi(optarg);
			break;
		case '?':
			fprintf (stderr, "\n invalid argument inserted \n");
			continue;
		}
	}
	fprintf (stderr,"Usage: [o:] %u  [p:]  %u [c:]  %u [s:]  %u  \n", _input->m_numOfCycls, _input->m_numOfProducers, _input->m_numOfConsumers, _input->m_queueSize);
	return ;
}

CommunucationChannels* CreateCommunicationChannel(size_t _sizeOfChannel)
{
    CommunucationChannels* communicationChannels;
    Queue* questionsQueue;
	Queue* answersQueue;
    
    communicationChannels = malloc(sizeof(CommunucationChannels));
    if(NULL ==  communucationChannels)
    {
        return NULL;
    }
    
	questionsQueue = QueueCreate(_sizeOfChannel);
	answersQueue = QueueCreate(_sizeOfChannel);
	
	if(NULL == questionsQueue || NULL == answersQueue)
	{
	    return NULL;
	}
    CommunucationChannels->m_qustionsQueue;
	CommunucationChannels->m_answersQueue;
	
	return CommunucationChannels;

}

ParticipationsData* CreateParticipations(size_t _numOfProducers, size_t _numOfConsumers, size_t _numOfProducersCycls, CommunucationChannels* _channels)
{
    ParticipationsData* data;
    
    data = malloc(sizeof(ParticipationsData));
    
    if(NULL == data)
    {
        return NULL;
    }
	
	data->m_consumers = CreateConsumers(_numOfConsumers);
	data->m_producers = CreateProducers(_numOfConsumers, _numOfProducersCycls);
	data->m_consumerContext = CreateConsumersContext(_channels->m_questionsQueue, _channels->m_answersQueue);
	data->m_producerContext = CreateProducerContext(_channels->m_questionsQueue, _channels->m_answersQueue,  _numOfProducersCycls);
	
	return data;
}

void ExecuteCommunication(ParticipationsData* _data)
{
    ExecuteConsumerThreads(_data->m_consumers, _data->m_consumerContext);
	ExecuteProducerThreads(_data->m_producers, _data->m_producerContext);
	
	ConsumersJoin(_data->m_consumers);
	ProducersJoin(_data->m_producers);
	
	return;
}

void DestroyChannelsAdnData(CommunucationChannels* _channels, ParticipationsData* _data)
{
    DestroyConsumerContextData(_data->m_consumers,_data->m_consumerContext);
	DestroyProducersData(_data->m_producers, _data->m_producerContext);
	QueueDestroy(_channels->m_questionsQueue);
	QueueDestroy(_channels->m_answersQueue);

}


