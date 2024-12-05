#ifndef SQLITEFILE_H
#define SQLITEFILE_H

#include "SQLiteCpp/SQLiteCpp.h"
#include <SQLiteCpp/VariadicBind.h>
#include <string>
#include <iostream>
#include "onlineservice.h"
#include "users.h"
#include <set>

class SQLiteClass{

private:
	
	SQLite::Database dbread;
	SQLite::Database dbwrite;

protected:

	void listUsers();
	void addUser(std::string);
	void removeUser(int);
	void removeDefaultService(int);
	friend class Admin;

public:

    SQLiteClass();
	~SQLiteClass();

	int createUser(std::string);
	
	int getUserID(std::string name);

	void ReadFromFile(std::vector<OnlineService>&);
	void populateUserService(std::vector<OnlineService>&,int);

	void addDefaultService(std::string, int, int, int, int, double, std::string);
	
	std::string getUserName(int);
	void addService(int, int);
	void removeService(int,int);
	std::set<int> getlistUsers();
	int getLastID();
};


#endif
