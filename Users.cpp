
#include "Users.h"
#include "sqlitefile.h"

std::map<int, int> User::getMap()
{
	std::map<int, int> tmp;

	tm* time = getTime();

	tmp[1] = 31;
	if ((time->tm_year + 1900 % 4 == 0 && time->tm_year + 1900 % 100 != 0) || time->tm_year + 1900 % 400 == 0)
	{
		tmp[2] = 29;
	}
	else
	{
		tmp[2] = 28;
	}

	tmp[3] = 31;
	tmp[4] = 30;
	tmp[5] = 31;
	tmp[6] = 30;
	tmp[7] = 31;
	tmp[8] = 31;
	tmp[9] = 30;
	tmp[10] = 31;
	tmp[11] = 30;
	tmp[12] = 31;

	return tmp;
}

User::User()
{
	name = "default";
	admin = false;
	userServices;
	defaultServices;
	ID = 0;
	mapYear = getMap();

	


}
User::User(std::string _name,bool _admin, SQLiteClass& db)
{
	name = _name;
	admin = _admin;
	db.ReadFromFile(defaultServices);
	ID = db.getUserID(name);
	db.populateUserService(userServices,ID);
	mapYear = getMap();

	
}

User::~User()
{
}

bool User::serviceIDExists(int tmp, std::vector<OnlineService>& service)
{
	bool answer = false;
	for (int i = 0; i < service.size(); i++)
	{
		if (tmp == service[i].getID())
		{
			answer = true;
			
		}
	}
	return answer;
}
void User::removeService(SQLiteClass& db)
{	
	

	
		int answer;
		std::cout << "Please select from the following services: \n";
		listServices(userServices);
		std::cout << std::endl;

		while (!(std::cin >> answer) || !serviceIDExists(answer,userServices))
		{
			std::cout << "Invalid Input!! Please enter a valid service: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		

		for (int i = 0; i < userServices.size(); i++)
		{
			if (answer == userServices[i].getID())
			{
				userServices.erase(userServices.begin() + i);
				db.removeService(ID, answer);
				
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

		
		std::cout << "Please enter payment month (1-12): ";
		while (!(std::cin >> month) || month < 1 || month > 12)
		{
			std::cout << "Invalid Input!! Please enter a valid month: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cout << "Please enter payment day (1-" << mapYear[month] <<"): ";
		while (!(std::cin >> day) || (day <= mapYear[month] && day > 0)) //Fix this
		{
			std::cout << "Invalid Input!! Please enter a valid day: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		

		tm* time = getTime();
		year = time->tm_year + 1900;

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
	int size = defaultServices.size() + 1;

	
		std::cout << "Please select from the following services: \n";
		listServices(defaultServices);
		std::cout << "[" << size << "]" << " Custom Service\n";

		while (!(std::cin >> answer) || !serviceIDExists(answer,defaultServices) && answer != defaultServices.size() +1)
		{
			std::cout << "Invalid Input!! Please enter a valid service: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

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
					
				}

			}
		}
		
	
}
