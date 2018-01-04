#ifndef __EVENT_H__
#define __EVENT_H__


#include <time.h>
#include<string>

class Payload;

class Event
{
public:
    Event(const std::string& _type = "type" , const std::string& _floor = "all floors", const std::string& _room = "all rooms", Payload* _pay = 0): m_type(_type), m_floor(_floor), m_room(_room), m_payLoad(_pay){}
	~Event (){}
    const std::string& GetType()const {return m_type;}
    const std::string& GetFloor()const{return m_floor;}
    const std::string& GetRoom()const{return m_room;}
    const Payload* GetPayload()const {return m_payLoad;}
private:
	Event (const Event& arguments);
    Event&operator=(const Event& arguments);
    
private:
	std::string m_type;
	std::string m_floor;
	std::string m_room;
	Payload* m_payLoad;
	
};
#endif /* __EVENT_H__ */

