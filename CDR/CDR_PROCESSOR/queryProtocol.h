
#ifndef __QPROTOCOL__
#define __QPROTOCOL__


typedef struct Query
{
	int		m_enum;
	int		m_operatorTuple;
	int		m_removeFlag;
	int		m_shutDownFlag;
	char	m_subscriberMSISDN[16];
	char	m_path[32];
} Query;

#endif
