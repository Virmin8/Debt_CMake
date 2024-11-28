#include "admin.h"

Admin::Admin() : User()
{

}

Admin::Admin(std::string name, bool admin, SQLiteClass& db) : User(name,admin,db)
{
	db.ReadFromFile(getDefaultServices());
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

void Admin::listServices()
{

	for (int i = 0; i < getDefaultServices().size(); i++)
	{
		getDefaultServices()[i].print();

	}
}

void Admin::removeService(SQLiteClass& db, std::vector<OnlineService>& service)
{
	bool work = false;
	


	int answer;
	std::cout << "Please select from the following services: \n";
	listServices();
	std::cout << std::endl;
	std::cin >> answer;

	for (int i = 0; i < service.size(); i++)
	{
		if (answer == service[i].getID())
		{
			service.erase(service.begin() + i);
			setDefaultServices(service);
			db.removeDefaultService(answer);
			work = false;
		}


	}
}


Admin::~Admin()
{

}
