#include "stdlib.h"
#include "HVAC.h"
#include "TempSensPayload.h"
#include <sstream> 

HVAC::HVAC(tr1::shared_ptr<AgentData> _data, HubInterface* _hub): Agent(_data, _hub)
{
 	SetMaxMin();
 	m_hub->Subscribe(this);
}
 
void HVAC::PushEvent (tr1::shared_ptr<Event> ptr)
{
	std::stringstream ss;
	ss << ((TempSensPayload*)ptr->GetPayload())->strCurTemp << ". ";
	
	if(((TempSensPayload*)ptr->GetPayload())->curTemp >= maxTemp)
	{
		ss << "Turn on HVAC! temp. is higher then :" << maxTemp << endl;
		m_data->m_logger->Write(ss.str(),m_data->m_ID);
		return;
	}
	
	if(((TempSensPayload*)ptr->GetPayload())->curTemp <= minTemp)
	{
		ss << "Turn off HVAC! temp. is lower then :" << minTemp << endl;
		m_data->m_logger->Write(ss.str(),m_data->m_ID);
		return;
	}	
}
 
bool HVAC::IsInterested(tr1::shared_ptr<Event> ptr)const
{
	return ptr->GetType() == "Temp" && ptr->GetFloor() == m_data->m_floor? true: false;

}

void HVAC::SetMaxMin()
{
	std::string minDelimiter = "lower:";
	std::string maxDelimiter = "upper:";
	
	int pos = m_data->m_config.find(maxDelimiter);
	maxDelimiter = m_data->m_config.substr(pos+6, pos+9);
	maxTemp= atoi(maxDelimiter.c_str()); 
	
	pos = m_data->m_config.find(minDelimiter);
	minDelimiter = m_data->m_config.substr(pos+6, pos+9);
	minTemp = atoi(minDelimiter.c_str()); 
}
