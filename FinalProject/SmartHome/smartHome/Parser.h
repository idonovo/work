#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <tr1/memory>
#include "AgentData.h"
#include "IParser.h"
using namespace std;


class Parser: public IParser<std::string>
{
public:

	Parser (const std::string&);
	virtual ~Parser ();
	
	void CloseFile ();
	virtual void SetConfig (const std::string&);
	virtual tr1::shared_ptr<AgentData> GetNextAgentData();

private:
	bool CheckMandatoryDetails(tr1::shared_ptr<AgentData>  agentData);
	void FillAgentData(string& line, tr1::shared_ptr<AgentData> agentData);
	Parser (const Parser& parser);
	Parser& operator= (const Parser& parser);
	
private:
	ifstream 		file;
	unsigned int  	curLine;
};


Parser::Parser(const std::string& _file):IParser(_file)
{
	file.open(m_config.c_str());
	curLine = 0;
}

template<class T>
Parser<T<:: ~Parser ()
{
	if(file.is_open())
	{
		file.close();
	}

}


//Parser::Parser (const Parser& parser)
//{
//	fileName = parser.fileName;
//	file.open(fileName.c_str());
//}

//Parser& Parser::operator= (const Parser& parser)
//{
//	if(this != &parser)
//	{
//		if(file.is_open())
//		{
//			file.close();
//		}
//		fileName = parser.fileName;
//		file.open(fileName.c_str());
//	}
//	return *this;
//}


//  /**
//   * @return AgentData*
//   */
//tr1::shared_ptr<AgentData> Parser::GetNextAgentData()
//{
//	string line;

//	if(file.eof())
//	{
//		string empty = "end of file";
//		throw empty;
//	}
//	tr1::shared_ptr<AgentData> agentData(new AgentData);
//	getline(file, agentData->m_ID);
//	++curLine;
//	
//	getline(file, line);
//	++curLine;
//	while(!line.empty())
//	{
//		FillAgentData(line, agentData);
//		getline(file, line);
//		++curLine;
//	}
//	
//	if(!CheckMandatoryDetails(agentData))
//	{
//		std::stringstream ss;
//		ss << agentData->m_ID << " bad config information on line" <<curLine;
//		throw ss.str();
//	} 

//	return agentData; 
//}

//void Parser::FillAgentData(string& line, tr1::shared_ptr<AgentData> agentData)
//{
//	string delimiter = " = ";
//	unsigned int pos; 
//	string type = line.substr(0, pos = line.find(delimiter));
//	line.erase(0, pos+delimiter.length());
//	
//	if(type == "type")
//	{
//		agentData->m_type = line;
//		return;  
//	}
//	if(type == "room")
//	{
//		agentData->m_room = line;
//		return;  
//	} 
//	if(type == "floor")
//	{
//		agentData->m_floor = line;
//		return;  
//	} 
//	if(type == "log")
//	{
//		agentData->m_log = line;
//		return;  
//	} 
//	if(type == "config")
//	{
//		agentData->m_config = line;
//		return;  
//	} 
//}

//bool Parser::CheckMandatoryDetails(tr1::shared_ptr<AgentData> agentData)
//{

//	if(agentData->m_type.empty())
//	{
//		return false;
//	}
//	if(agentData->m_floor.empty())
//	{
//		return false;
//	}
//	if(agentData->m_room.empty())
//	{
//		return false;
//	}
//	return true;
//}
//  /**
//   */
//void Parser::CloseFile()
//{
//	if(file.is_open())
//	{
//		file.close();
//	}
//}

#endif // PARSER_H
