#ifndef __PAYLOAD_H__
#define __PAYLOAD_H__

class Payload
{
public:
    Payload(){}
	virtual ~Payload (){}
    
private:
	Payload (const Payload& _arg);
    Payload&operator=(const Payload& _arg);
};

#endif /* __PAYLOAD_H__ */

