
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
using namespace std;
#include <tr1/memory>
#include "AgentData.h"

class Parser
{
public:


	Parser (){};
	virtual ~Parser ();
	
	Parser (const string& file);
	virtual tr1::shared_ptr<AgentData> GetNextAgentData();
	void CloseFile ();
	void OpenFile (const string& file);

private:
	bool CheckMandatoryDetails(tr1::shared_ptr<AgentData>  agentData);
	void FillAgentData(string& line, tr1::shared_ptr<AgentData> agentData);
	Parser (const Parser& parser);
	Parser& operator= (const Parser& parser);
	
private:
	ifstream 		file;
	string			fileName;
	unsigned int  	curLine;
};

#endif // PARSER_H
