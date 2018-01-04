

#include <stdlib.h>
#include <iostream>
#include "DataBase.h"

using namespace sh;

int main(void)
{

	DB_info info;
	info.m_ip = "tcp://127.0.0.1:3306";
	info.m_user = "root";
	info.m_password = "student";
	info.m_schema = "SmartBuilding";
	
	DataBase dataBase(info);
	std::tr1::shared_ptr<QueryRes> res = dataBase.QueryByID("Agents", 1, 6);
	
	for(std::vector<std::string>::iterator it = res->m_vec.begin(); it != res->m_vec.end(); ++it)
	{
    	std::cout << *it << std::endl;
	}
	
	res = dataBase.QueryTableDataBase("Agents", 6);
	
	for(std::vector<std::string>::iterator it = res->m_vec.begin(); it != res->m_vec.end(); ++it)
	{
    	std::cout << *it << std::endl;
	}

//	
//cout << endl;
//cout << "Running 'SELECT 'Hello World!'" << endl;

//try {
//  sql::Driver *driver;
//  sql::Connection *con;
//  sql::Statement *stmt;
//  sql::ResultSet *res;

//  /* Create a connection */
//  driver = get_driver_instance();
//  con = driver->connect("tcp://127.0.0.1:3306", "root", "student");
//  /* Connect to the MySQL test database */
//  con->setSchema("SmartBuilding");

//  stmt = con->createStatement();
//  res = stmt->executeQuery("show tables");
//	while (res->next())
//	{
//		cout << res->getString(1) << endl;                
//	}
//	  res = stmt->executeQuery("show tables");
//	while (res->next())
//	{
//		cout << res->getString(1) << endl;                
//	}

//  delete res;
//  delete stmt;
//  delete con;

//} catch (sql::SQLException &e) {
//  cout << "# ERR: SQLException in " << __FILE__;
//  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//  cout << "# ERR: " << e.what();
//  cout << " (MySQL error code: " << e.getErrorCode();
//  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//}

//cout << endl;

return EXIT_SUCCESS;
}
