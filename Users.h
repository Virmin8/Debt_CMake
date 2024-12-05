#ifndef USERS_H
#define USERS_H
#define NOMINMAX
#include <string>
#include "sqlitefile.h"
#include <map>
#include "functions.h"

class SQLiteClass;

class User {
private:
	std::string name;
	bool admin;
	std::vector<OnlineService> userServices;
	std::vector<OnlineService> defaultServices;
	int ID;
	std::map<int, int> mapYear;

public:

	User();
	User(std::string,bool,SQLiteClass&);
	~User();

	void addService(SQLiteClass& );
	virtual void removeService(SQLiteClass& );

	virtual void listServices(std::vector<OnlineService>& services);
	
	std::string getName();
	bool getAdmin();
	int getID();

	void customService(SQLiteClass&);

	std::vector<OnlineService> getDefaultServices();
	std::vector<OnlineService> getUsertServices();
	void setDefaultServices(std::vector<OnlineService>&);
	
};
#endif