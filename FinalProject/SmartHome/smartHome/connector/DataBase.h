#ifndef __MYCONNECTOR_H__
#define __MYCONNECTOR_H__

#include "mysql_connection.h"
#include <tr1/memory>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <vector>


namespace sh
{

struct QueryRes
{
	std::vector<std::string> m_vec;
};

struct DB_info
{
	std::string m_ip;
	std::string m_user;
	std::string m_password;
	std::string m_schema;
};

class DataBase
{
public:
	explicit DataBase (){};
	explicit DataBase (const DB_info&);
	virtual ~DataBase ();
	
	bool SetDataBase(const DB_info&);
	bool AddData(const std::string&);
	
	std::tr1::shared_ptr<QueryRes> QueryData(const std::string&, std::size_t);
	std::tr1::shared_ptr<QueryRes> QueryByID(const std::string&, std::size_t, std::size_t);
	std::tr1::shared_ptr<QueryRes> QueryTableDataBase(const std::string&, std::size_t);

private:
	
	std::tr1::shared_ptr<sql::ResultSet> GetQueryRes(const std::string&);
	bool FillRow(std::string& str, std::tr1::shared_ptr<sql::ResultSet> _res, std::size_t _coulmns);
	std::string CreateQuery(const std::string& , std::size_t);
	std::string CreateQuery(const std::string& , std::size_t, std::size_t);
	
	DB_info m_info;
	sql::Driver* m_driver;
	std::tr1::shared_ptr<sql::Connection> m_connect;

};


}

#endif /* __MYCONNECTOR_H__ */

