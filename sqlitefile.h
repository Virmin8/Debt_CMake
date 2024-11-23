#ifndef SQLITEFILE_H
#define SQLITEFILE_H

#include "SQLiteCpp/SQLiteCpp.h"
#include <SQLiteCpp/VariadicBind.h>
#include <string>
#include <iostream>
#include "onlineservice.h"
//#include "admin.h"

class SQLiteClass{

private:
	
	SQLite::Database dbread;
	SQLite::Database dbwrite;

public:

    SQLiteClass();
	~SQLiteClass();

	void addUser(std::string); //make private
	void removeDatabase(std::string, std::string);
	void ReadFromFile(std::vector<OnlineService>&);
	void addService(std::string, int, int, int, int, double, std::string);
	//friend class admin;
};


#endif
