#ifndef ADMIN_H
#define ADMIN_H

#include "Users.h"
#include <set>


class SQLiteClass;

class Admin :public User
{
	
public:

	Admin();
	Admin(std::string,bool, SQLiteClass&);
	~Admin();

	void adminAddUser(SQLiteClass&, std::string);
	void adminRemoveUser(SQLiteClass&);
	void adminListUsers(SQLiteClass&);
	void listServices();
	void removeService(SQLiteClass&, std::vector<OnlineService>&);
	
	
};
#endif