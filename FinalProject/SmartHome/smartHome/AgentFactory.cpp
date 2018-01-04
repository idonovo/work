#include <dirent.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "Agent.h"
#include "AgentFactory.h"


typedef void* (*AgentCreate)(tr1::shared_ptr<AgentData>  data, const string& type, HubInterface* _hub);

typedef void (*GetAgentType)(map <string, string>&);

Agent* AgentFactory::CreateAgent(tr1::shared_ptr<AgentData>  data, const string& type, HubInterface* _hub)
{
	
	if(!_hub || !data || type.empty())
	{
		throw "not init";
	}

	std::map <string, string>::iterator it =  m_typesAndFiles.find(type);
	if(it ==  m_typesAndFiles.end())
	{
		throw "type not found";
	}
	
	void  *handle = dlopen(it->second.c_str(), RTLD_LAZY);
	if(!handle)
	{
		throw "could not open file";
	}
  	
  	AgentCreate func = (AgentCreate)dlsym(handle, "AgentCreate");
	return func? (Agent*) func(data, type, _hub) : 0;	
	
}

bool AgentFactory::MapSO(const string& SOfile)
{	
	void  *handle = dlopen(SOfile.c_str(), RTLD_LAZY);
	if(!handle)
	{
		return false;
	}
  	
  	GetAgentType func = (GetAgentType)dlsym(handle, "GetAgentType");
    func(m_typesAndFiles);
    dlclose(handle);
    return true;

}

void AgentFactory::MapDir(const string& _path)	
{
	struct dirent** namelist;
	
	int numOfFiles = scandir(_path.c_str(), &namelist, NULL, alphasort);
	
    if (numOfFiles == -1)
    {
		throw "no files in directory";
    }

    for (int i = 0; i < numOfFiles; i += 1)
    {
       if((string)namelist[i]->d_name!= "." && (string)namelist[i]->d_name!= "..")
       {
          string file = (string)"../SOS/" + (string)namelist[i]->d_name;
		  if(!MapSO(file))
		  {
		  	throw "file cannot open"; 
		  }  
       }
       free(namelist[i]);    
    }
    free(namelist);
    
    return;
}

