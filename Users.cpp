#include "Users.h"


User::User()
{
	name = "default";
	admin = false;
}
User::User(std::string _name,bool _admin)
{
	name = _name;
	admin = _admin;
}

User::~User()
{
}

void User::removeService()
{
}
void User::listUserServices()
{
}
std::string User::getName()
{
	return name;
}
bool User::getAdmin()
{
	return admin;
}

void User::addService()
{
}