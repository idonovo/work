
#include "TempSensor.h"
#include "TempSensPayload.h"
#include <stdlib.h>  
#include <unistd.h>
#include <sstream> 

TempSensor:: TempSensor(tr1::shared_ptr<AgentData> _data, HubInterface* _hub): Agent(_data, _hub)
{
	SetMaxMin();
	if (0 != pthread_create(&threadID, NULL, TempSensor::Launch, (void*)this))
	{
		throw "thread create fail"; 
	}
}

TempSensor::~TempSensor()
{
	pthread_join(threadID, 0);
}

void TempSensor::SensorRoutine()
{
	while(1)
	{
		sleep(period);
		TempSensPayload* payload = new TempSensPayload;
		std::stringstream ss;
		ss << "The temperature in floor " << m_data->m_floor << " is: " << (payload->curTemp  = (rand() %(maxTemp - minTemp)) + minTemp)<< endl ;
		m_data->m_logger->Write(payload->strCurTemp = ss.str(), m_data->m_ID); 
		tr1::shared_ptr<Event> event(new Event("Temp", m_data->m_floor, m_data->m_room, payload));
		PublishEvent(event);
	}
}

void* TempSensor::Launch(void* context)
{
	TempSensor* sens = (TempSensor*)context;
	sens->SensorRoutine();
	
}

void TempSensor::SetMaxMin()
{

	std::string minDelimiter = "lower:";
	std::string maxDelimiter = "upper:";
	std::string perDelimiter = "period:";
	
	int pos = m_data->m_config.find(maxDelimiter);
	maxDelimiter = m_data->m_config.substr(pos+6, pos+9);
	maxTemp= atoi(maxDelimiter.c_str()); 
	
	pos = m_data->m_config.find(minDelimiter);
	minDelimiter = m_data->m_config.substr(pos+6, pos+9);
	minTemp = atoi(minDelimiter.c_str());
	
	pos = m_data->m_config.find(perDelimiter);
	perDelimiter = m_data->m_config.substr(pos+7, pos+9);
	period = atoi(perDelimiter.c_str());   
}
