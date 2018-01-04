#include "DataBase.h"
#include <sstream> 

namespace sh
{

DataBase::DataBase (const DB_info& _info): m_info( _info),
m_driver(get_driver_instance()), 
m_connect(m_driver->connect(m_info.m_ip, m_info.m_user, m_info.m_password)) 
{
	 m_connect->setSchema(m_info.m_schema);
}

DataBase::~DataBase(){}

bool DataBase::SetDataBase(const DB_info& _info)
{
	m_info = _info;
	m_driver = get_driver_instance(); 
	std::tr1::shared_ptr<sql::Connection> connect(m_driver->connect(m_info.m_ip, m_info.m_user, m_info.m_password));
	m_connect = connect;	
	m_connect->setSchema(m_info.m_schema);
	return true;
}

bool DataBase::AddData(const std::string& _req)
{
	std::tr1::shared_ptr<sql::Statement> state(m_connect->createStatement());
	
	try
	{
		state->executeQuery(_req);
			
	}catch(sql::SQLException &e){
		return false;
	}
	return true;
}

std::tr1::shared_ptr<sql::ResultSet> DataBase::GetQueryRes(const std::string& _req)
{
	std::tr1::shared_ptr<sql::Statement> state(m_connect->createStatement());
	std::tr1::shared_ptr<sql::ResultSet> res(state->executeQuery(_req));
	return res;
}


bool DataBase::FillRow(std::string& str, std::tr1::shared_ptr<sql::ResultSet> _res, std::size_t _coulmns)
{
	if(_res->next())
	{
		std::size_t i = 0;
		std::stringstream ss;	
		
		while (i<_coulmns)
		{
			ss << "coulmn number " << i << ": " <<_res->getString(++i) << "\n";
		}
		str = ss.str();
		return true;           
	}
	return false;
}

std::string DataBase::CreateQuery(const std::string& _req, std::size_t coulmns)
{
	std::stringstream ss;
	ss << "select * from " << _req;
	std::cout << ss.str();
	return ss.str();
}

std::string DataBase::CreateQuery(const std::string& _req, std::size_t _ID, std::size_t coulmns)
{
	std::stringstream ss;
	ss << "select * from " << _req << " where id = " << _ID;
	std::cout << ss.str();
	return ss.str();
}

std::tr1::shared_ptr<QueryRes> DataBase::QueryTableDataBase(const std::string& _req, std::size_t _coulmns)
{
	std::tr1::shared_ptr<QueryRes> Qres (new QueryRes);
	std::tr1::shared_ptr<sql::ResultSet> SuccesRes;
	std::string temp;
	try
	{
		
		SuccesRes = GetQueryRes(CreateQuery(_req, _coulmns));
		
	}catch(sql::SQLException &e){
		
		return Qres;
	}
	
	
	while(FillRow(temp, SuccesRes, _coulmns))
	{
		Qres->m_vec.push_back(temp); 
	}
	return Qres;
}

std::tr1::shared_ptr<QueryRes> DataBase::QueryByID(const std::string& _req, std::size_t _ID, std::size_t _coulmns)
{

	std::tr1::shared_ptr<QueryRes> Qres (new QueryRes);
	std::tr1::shared_ptr<sql::ResultSet> SuccesRes;
	std::string temp;
	try
	{
		SuccesRes = GetQueryRes(CreateQuery(_req, _ID,_coulmns));
		
	}catch(sql::SQLException &e){
		
		return Qres;
	}
	
	FillRow(temp, SuccesRes, _coulmns);
	Qres->m_vec.push_back(temp); 
	return Qres;
}

std::tr1::shared_ptr<QueryRes> DataBase::QueryData(const std::string& _req, std::size_t _coulmns)
{
	std::tr1::shared_ptr<QueryRes> Qres (new QueryRes);
	std::tr1::shared_ptr<sql::ResultSet> SuccesRes;
	std::string temp;
	try
	{
		SuccesRes = GetQueryRes(_req);
		
	}catch(sql::SQLException &e){
		
		return Qres;
	}
	
	FillRow(temp, SuccesRes, _coulmns);
	Qres->m_vec.push_back(temp); 
	return Qres;
}

}

