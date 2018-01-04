#ifndef __VIRTIO_H__
#define __VIRTIO_H__

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


enum Status
{
	ok_e, 
	cant_open_file_e, 
	bad_access_e, 
	writeErr_e,
    readErr_e
};

class virtIO_t
{


public:
    virtIO_t();
	virtIO_t (const string& _path, const string& _mode);
	virtual ~virtIO_t ();
	
	bool Open(const string& _path, const string& _mode);
	void Close();
	
	virtual bool SetPath(const string& _path);
	virtual bool SetMode(const string& _path);
	
	virtual long int Length() const;
	
	virtual virtIO_t& operator << (char _obj) =0;
	
	virtual virtIO_t& operator << (short _obj) =0;
	virtual virtIO_t& operator << (int _obj) =0;
	virtual virtIO_t& operator << (long _obj) =0;
	virtual virtIO_t& operator << (float _obj) =0;
	virtual virtIO_t& operator << (unsigned char _obj) =0;
	virtual virtIO_t& operator << (unsigned short _obj) =0;
	virtual virtIO_t& operator << (unsigned int _obj) =0;
	virtual virtIO_t& operator << (unsigned long _obj) =0;
	virtual virtIO_t& operator << (double _obj) =0;
	
	virtual virtIO_t& operator >> (char &_obj) =0;
	virtual virtIO_t& operator >> (short &_obj ) =0;
	virtual virtIO_t& operator >> (int &_obj) =0;
	virtual virtIO_t& operator >> (long &_obj) =0;
	virtual virtIO_t& operator >> (float &_obj) =0;
	virtual virtIO_t& operator >> (unsigned char &_obj) =0;
	virtual virtIO_t& operator >> (unsigned short &_obj) =0;
	virtual virtIO_t& operator >> (unsigned int &_obj) =0;
	virtual virtIO_t& operator >> (unsigned long &_obj) =0;
	virtual virtIO_t& operator >> (double &_obj) =0; 
		
private:
	virtIO_t (const virtIO_t& arguments){};
    virtual virtIO_t&operator=(const virtIO_t& arguments){};
    bool CheckMode(const string& _path);
    
protected:
	FILE* 		m_fp;
	char 		m_mode[3];
	string 		m_path;

};
#endif /* __VIRTIO_H__ */

