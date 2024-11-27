#ifndef ADMIN_H
#define ADMIN_H

#include "Users.h"
#include "sqlitefile.h"

class SQLiteClass;

class Admin :public User
{

public:

	Admin();
	Admin(std::string,bool);
	~Admin();

	void adminAddUser(SQLiteClass&, std::string);
	void adminRemoveUser(SQLiteClass&, std::string);
	void adminListUsers(SQLiteClass&);

	
};
#endif