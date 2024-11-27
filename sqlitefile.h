#ifndef SQLITEFILE_H
#define SQLITEFILE_H

#include "SQLiteCpp/SQLiteCpp.h"
#include <SQLiteCpp/VariadicBind.h>
#include <string>
#include <iostream>
#include "onlineservice.h"
#include "Users.h"
#include "admin.h"

class SQLiteClass{

private:
	
	SQLite::Database dbread;
	SQLite::Database dbwrite;

protected:

	void listUsers();
	void addUser(std::string);
	void removeUser(std::string);

	friend class Admin;

public:

    SQLiteClass();
	~SQLiteClass();

	int createUser(std::string);
	
	void removeService(std::string);
	void ReadFromFile(std::vector<OnlineService>&);
	void addDefaultService(std::string, int, int, int, int, double, std::string);
};


#endif
