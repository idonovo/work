#ifndef __MYSELECTSERVER_H__
#define __MYSELECTSERVER_H__

#include "Server.h"
#include "Select.h"

namespace Netcpp
{

template <class T>
class SelectServer: public Server<T> 
{
public:
	SelectServer(const Peer_info&, std::tr1::shared_ptr<T> , std::size_t _queueSize);
	virtual ~SelectServer ();
	virtual void Run();

private:
	void HandleServer();
	void HandleList();
	Select* m_select;
};

template <class T>
SelectServer<T>::SelectServer(const Peer_info& _info, std::tr1::shared_ptr<T> _t, std::size_t _queueSize): 
Server<T>(_info, _t, _queueSize), 
m_select(new Select)
{}

template <class T>
SelectServer<T>:: ~SelectServer ()
{
	delete m_select;
}

template <class T>
void SelectServer<T>::Run()
{
	Server<T>::m_isRunning = true;
	std::size_t activeSokets;
	std::tr1::shared_ptr<Selectable> acceptor(Server<T>::m_acceptor);
	
	while(Server<T>::m_isRunning)
	{
		activeSokets = m_select->GetNumOfActiveSelectable();
		
		if(activeSokets)
		{
			if(m_select->IsSet(acceptor))
			{			
				HandleServer();
			}
			HandleList();
		}
	}
}

template <class T>
void SelectServer<T>::HandleServer()
{
	std::tr1::shared_ptr<Socket> newSock;
	try
    {
		newSock = Server<T>::m_acceptor->Accept();
	    newSock->SetNonBlocking();	
	    if(Server<T>::m_app->ApproveClient(newSock))
	    {
		    Server<T>::m_socketsList.push_front (newSock);
		    std::tr1::shared_ptr<Selectable>newSelctable(&(*newSock));
		    m_select->AddSelectable(newSelctable);						
	    }
    }
    catch(Err_TryAgain& err)
    {}

}

template <class T>
void SelectServer<T>::HandleList()
{
	

}

}
#endif /* __MYSELECTSERVER_H__ */

