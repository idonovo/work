
#include "Parser.h"
#include <sstream>



Parser:: ~Parser ()
{
	if(file.is_open())
	{
		file.close();
	}

}

Parser::Parser (const string& _file)
{
	fileName = _file;
	file.open(fileName.c_str());
	curLine = 0;
}

Parser::Parser (const Parser& parser)
{
	fileName = parser.fileName;
	file.open(fileName.c_str());
}

Parser& Parser::operator= (const Parser& parser)
{
	if(this != &parser)
	{
		if(file.is_open())
		{
			file.close();
		}
		fileName = parser.fileName;
		file.open(fileName.c_str());
	}
	return *this;
}


  /**
   * @return AgentData*
   */
tr1::shared_ptr<AgentData> Parser::GetNextAgentData()
{
	string line;

	if(file.eof())
	{
		string empty = "end of file";
		throw empty;
	}
	tr1::shared_ptr<AgentData> agentData(new AgentData);
	getline(file, agentData->m_ID);
	++curLine;
	
	getline(file, line);
	++curLine;
	while(!line.empty())
	{
		FillAgentData(line, agentData);
		getline(file, line);
		++curLine;
	}
	
	if(!CheckMandatoryDetails(agentData))
	{
		std::stringstream ss;
		ss << agentData->m_ID << " bad config information on line" <<curLine;
		throw ss.str();
	} 

	return agentData; 
}

void Parser::FillAgentData(string& line, tr1::shared_ptr<AgentData> agentData)
{
	string delimiter = " = ";
	unsigned int pos; 
	string type = line.substr(0, pos = line.find(delimiter));
	line.erase(0, pos+delimiter.length());
	
	if(type == "type")
	{
		agentData->m_type = line;
		return;  
	}
	if(type == "room")
	{
		agentData->m_room = line;
		return;  
	} 
	if(type == "floor")
	{
		agentData->m_floor = line;
		return;  
	} 
	if(type == "log")
	{
		agentData->m_log = line;
		return;  
	} 
	if(type == "config")
	{
		agentData->m_config = line;
		return;  
	} 
}

bool Parser::CheckMandatoryDetails(tr1::shared_ptr<AgentData> agentData)
{

	if(agentData->m_type.empty())
	{
		return false;
	}
	if(agentData->m_floor.empty())
	{
		return false;
	}
	if(agentData->m_room.empty())
	{
		return false;
	}
	return true;
}
  /**
   */
void Parser::CloseFile()
{
	if(file.is_open())
	{
		file.close();
	}
}

  /**
   * @return bool
   * @param  file
   */
void Parser::OpenFile (const string& _file)
{
	
	if(file.is_open())
	{
		file.close();
	}
	fileName = _file;
	file.open(fileName.c_str());
	curLine = 0;

}
