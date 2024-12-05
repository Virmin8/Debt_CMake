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

void Admin::adminRemoveUser(SQLiteClass& db) // Fix this
{
	int answer;
	std::cout << "Please select UserID: \n";
	std::set<int> list = db.getlistUsers();
	std::cout << list.size();

	while (!(std::cin >> answer) || list.find(answer) == list.end());
	{
		std::cout << "Invalid Input!! Please enter a valid User: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cout << "Fuck";
	db.removeUser(answer);
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
	
	int answer;
	std::cout << "Please select from the following services: \n";
	listServices();
	std::cout << std::endl;

	while (!(std::cin >> answer) || !serviceIDExists(answer, service))
	{
		std::cout << "Invalid Input!! Please enter a valid service: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	for (int i = 0; i < service.size(); i++)
	{
		if (answer == service[i].getID())
		{
			service.erase(service.begin() + i);
			setDefaultServices(service);
			db.removeDefaultService(answer);
			
		}


	}
}


Admin::~Admin()
{

}
