#include "admin.h"

Admin::Admin() : User()
{

}

Admin::Admin(std::string name, bool admin) : User(name,admin)
{

}

void Admin::adminAddUser(SQLiteClass& db, std::string name)
{
	db.addUser(name);
}

void Admin::adminRemoveUser(SQLiteClass& db, std::string name)
{
	db.removeUser(name);
}

void Admin::adminListUsers(SQLiteClass& db)
{
	db.listUsers();
}

Admin::~Admin()
{

}
