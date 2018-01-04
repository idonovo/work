#ifndef __TEMPPAYLOAD_H__
#define __TEMPPAYLOAD_H__


#include "Payload.h"


class TempSensPayload: public Payload
{
public:
    TempSensPayload(): Payload(){}
	virtual~TempSensPayload (){}
	
	std::string strCurTemp;
	int	curTemp;	
private:
	TempSensPayload (const TempSensPayload& arguments);
    TempSensPayload&operator=(const TempSensPayload& arguments);
    

};
#endif /* __TEMPPAYLOAD_H__ */

