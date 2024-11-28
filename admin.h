#ifndef ADMIN_H
#define ADMIN_H

#include "Users.h"


class SQLiteClass;

class Admin :public User
{
	
public:

	Admin();
	Admin(std::string,bool, SQLiteClass&);
	~Admin();

	void adminAddUser(SQLiteClass&, std::string);
	void adminRemoveUser(SQLiteClass&, std::string);
	void adminListUsers(SQLiteClass&);
	void listServices();
	void removeService(SQLiteClass&, std::vector<OnlineService>&);
	
	
};
#endif