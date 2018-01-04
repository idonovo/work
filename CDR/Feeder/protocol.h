#ifndef __PROTOCOL__
#define __PROTOCOL__


#include <stddef.h>

/* shared adt of proccessor and feeder. the feeder will parse CDR files into the struct and then deliver it to the proccessor using TransmissionData api */
struct CdrData 
{
    char   	m_imsi[16];
    char	m_msidn[16]; 
    char	m_imei[16];
    char    m_opratorBrandName[64]; 
    int     m_tuple;
   	char    m_type; /* a = moc  b = mtc c = outgoing sms d = incoming sms e = web */
    char   	m_date[16];
    char   	m_time[16];
   	size_t  m_duration;
   	size_t	m_downloaded;
    size_t	m_uploaded;
    char	m_ParMSIDN[16]; 
    char   	m_ParOprator; /* a = inside operator b = outside operator */
    int   	m_ParOpratorTuple; 
};

#endif
