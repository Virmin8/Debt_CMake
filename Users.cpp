#include "Users.h"
#include "sqlitefile.h"

User::User()
{
	name = "default";
	admin = false;
	userServices;
	defaultServices;
	ID = 0;

}
User::User(std::string _name,bool _admin, SQLiteClass& db)
{
	name = _name;
	admin = _admin;
	db.ReadFromFile(defaultServices);
	ID = db.getUserID(name);
	db.populateUserService(userServices,ID);

}

User::~User()
{
}

void User::removeService(SQLiteClass& db)
{	
	bool work = false;

	
		int answer;
		std::cout << "Please select from the following services: \n";
		listServices(userServices);
		std::cout << std::endl;
		std::cin >> answer;

		for (int i = 0; i < userServices.size(); i++)
		{
			if (answer == userServices[i].getID())
			{
				userServices.erase(userServices.begin() + i);
				db.removeService(ID, answer);
				work = false;
			}
			

		}
	
}
void User::listServices(std::vector<OnlineService>& services)
{
	for (int i = 0; i < services.size(); i++)
	{
		services[i].print();

	}
	
}
std::string User::getName()
{
	return name;
}
bool User::getAdmin()
{
	return admin;
}

int User::getID()
{
	return ID;
}

void User::customService(SQLiteClass& db)
{
	std::string name;
	int everyfemonths;
	int day;
	int month;
	int year;
	double cost;
	std::string symbol = "ZAR";
	bool exists = true;
	std::cout << "\nAdding new Service:";
	std::cout << "\nPlease enter service name: ";
	std::cin >> name;

	while (exists)
	{


		for (int i = 0; i < defaultServices.size(); i++)
		{
			if (name == defaultServices[i].getName())
			{
				std::cout << "Service already Exists!!!\n";
				std::cout << "\nPlease enter service name: ";
				std::cin >> name;
				exists = true;

			}
			else
				exists = false;
		}
	}
	std::cout << "Please enter every few months: ";
	std::cin >> everyfemonths;
	std::cout << "Please enter payment day: ";
	std::cin >> day;
	std::cout << "Please enter payment month: ";
	std::cin >> month;
	std::cout << "Please enter payment year: ";
	std::cin >> year;
	std::cout << "Please enter payment cost: ";
	std::cin >> cost;
	/*std::cout << "Please enter Currency Symbol? :";
	std::cin >> symbol;*/
	std::cout << "\n";

	OnlineService tmp(db.getLastID() + 1, name, everyfemonths, day, month, year, cost, symbol);
	defaultServices.push_back(tmp);
	userServices.push_back(tmp);

	db.addDefaultService(name, everyfemonths, day, month, year, cost, symbol);
	db.addService(ID, defaultServices.size());
}

std::vector<OnlineService> User::getDefaultServices()
{
	return defaultServices;
}

std::vector<OnlineService> User::getUsertServices()
{
	return userServices;
}

void User::setDefaultServices(std::vector<OnlineService>& s)
{
	defaultServices = s;
}

void User::addService(SQLiteClass& db)
{
	int answer;
	bool work = false;

	
		std::cout << "Please select from the following services: \n";
		listServices(defaultServices);
		std::cout << "[" << defaultServices.size() +1 << "]" << " Custom Service\n";
		std::cin >> answer;

		if (answer == defaultServices.size() + 1)
		{
			customService(db);
		}
		else
		{
			for (int i = 0; i < defaultServices.size(); i++)
			{
				if (answer == defaultServices[i].getID())
				{
					userServices.push_back(defaultServices[i]);
					db.addService(ID, answer);
					work = true;
				}

			}
		}
		
	
}
