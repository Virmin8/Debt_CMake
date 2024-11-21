#include "functions.h"


void ReadFromFile(std::vector<OnlineService> &service)
{
    try
    {
        
        SQLite::Database    db("../Services.db");

        
        SQLite::Statement   query(db, "SELECT * FROM Test");

        
        while (query.executeStep())
        {
            OnlineService onlineservices(query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3), query.getColumn(4), query.getColumn(5), query.getColumn(6));
            service.push_back(onlineservices);

            
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

}

/*void WriteToFile(std::vector<OnlineService>& Services)
{
   /* std::string filename = "../UserServices.txt";
    std::ofstream fileout;

   
   
    std::cout << "Saving!!\n\n";
    
    
        
        fileout.open(filename);
        if (!fileout.is_open())
        {
            std::cout << "File cannot be read!!" << std::endl; //Needs error implementation, on what the program should do 
        }
        else
        {
            for (int i = 0; i < Services.size(); i++)
            {
                fileout << Services[i].getName() << " " << Services[i].getEveryfewMonths() << " " << Services[i].getDay() << " " << Services[i].getMonth() << " " << Services[i].getYear() << " " << Services[i].getCost() << " " << Services[i].getSymbol() << std::endl;

            }
            if (fileout.is_open())
            {
                fileout.close();
            }
        }

    try
    {
        SQLite::Database    db("../Services.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        db.exec("DROP TABLE IF EXISTS User");

        db.exec("CREATE TABLE User (Name TEXT PRIMARY KEY, Monthly INTEGER, Day INTEGER, Month INTEGER, Year INTEGER, Cost REAL, Currency TEXT)");

        SQLite::Transaction transaction(db);
        SQLite::Statement query{ db, "INSERT INTO User (Name) VALUES (?)" };


        for (int i = 0; i < Services.size(); i++)
        {
            

            
                query.bind(1, Services[i].getName());
                query.exec();
                query.reset();
            

            // Commit transaction
            transaction.commit();
        }
        
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    
}*/

double TotalMonthly(int month, std::vector<OnlineService>& Services)
{
    tm* time = getTime();

    double total = 0.00;
    for (int i = 0; i < Services.size(); i++)
    {
        if (Services[i].getMonth() == month || Services[i].getEveryfewMonths() == 1)
        {
            if (Services[i].getConvertedCost() == 0)
            {
                total += Services[i].getCost();
            }
            else
            {
                total += Services[i].getConvertedCost();
            }
            
        }
    }
    return total;
}

double TotalYearly(std::vector<OnlineService> &services)
{
    double total = 0.00;
    for (int i = 1; i < 13; i++)
    {
        total += TotalMonthly(i, services);
    }
    return total;
}

tm* getTime()
{
    std::time_t timestamp = std::time(0);
    std::tm* now = std::localtime(&timestamp);

    return now;
}

double RestMonthly(int month, std::vector<OnlineService>& Services)
{
    tm* time = getTime();
    double total = 0.00;
    for (int i = 0; i < Services.size(); i++)
    {
        if (Services[i].getMonth() == month || Services[i].getEveryfewMonths() == 1)
        {
            
            if (Services[i].getDay() >= time->tm_mday)
            {
                if (Services[i].getConvertedCost() == 0)
                {
                    total += Services[i].getCost();
                }
                else
                {
                    total += Services[i].getConvertedCost();
                }
            }

        }
    }
    return total;
}

double RestYearly(std::vector<OnlineService>& Services)
{
    tm* time = getTime();
    double total = RestMonthly(time->tm_mon + 1, Services);

    for (int i = time->tm_mon + 2; i < 13; i++)
    {
        total += TotalMonthly(i, Services);
    }
    return total;
}

void print(int month, std::vector<OnlineService>& Services)
{
    tm* time = getTime();
    int tmpmonth = time->tm_mon + 1;
    int tmpday = time->tm_mday;
    int tmpyear = time->tm_year + 1900;
    

    
    for (int i = 0; i < Services.size(); i++)
    {
        int year = 0;
        std::string paid = "No";
        SetColour(91);

        if (Services[i].getMonth() == month || Services[i].getEveryfewMonths() == 1)
        {
                if (month < time->tm_mon + 1)
                {
                    SetColour(92);
                    paid = "Yes";
                }
                else if (month == time->tm_mon + 1 && Services[i].getDay() <= time->tm_mday)
                {
                    SetColour(92);
                    paid = "Yes";
                }
                if (Services[i].getEveryfewMonths() == 12)
                {
                    year = -1;
                }
          
            Services[i].print(month, year, paid);
            ResetColour();
           
        }
        
    }
    
}

void ListServices(std::vector<OnlineService>& Services)
{
    std::cout << "\nYour current Services: \n";
    for (int i = 0; i < Services.size(); i++)
    {
        Services[i].print();

    }

}

void addService(std::vector<OnlineService>& Services)
{
    std::string name;
    int everyfemonths;
    int day;
    int month;
    int year;
    double cost;
    std::string symbol;
    std::cout << "\nAdding new Service:";
    std::cout << "\nPlease enter service name? :";
    std::cin >> name;
    std::cout << "Please enter every few months? :";
    std::cin >> everyfemonths;
    std::cout << "Please enter payment day: ";
    std::cin >> day;
    std::cout << "Please enter payment month? :";
    std::cin >> month;
    std::cout << "Please enter payment year? :";
    std::cin >> year;
    std::cout << "Please enter payment cost? :";
    std::cin >> cost;
    std::cout << "Please enter Currency Symbol? :";
    std::cin >> symbol;

    OnlineService tmp(name, everyfemonths, day, month, year, cost, symbol);
    Services.push_back(tmp);
}

void removeService(std::vector<OnlineService>& Services)
{
    std::string name;

    std::cout << "\nPlease enter the Service name you wish to remove, the options are: ";

    for (int i = 0; i < Services.size(); i++)
    {
        std::cout << "\n" << Services[i].getName();

    }
    std::cout << "\n";
    std::cin >> name;

    for (int i = 0; i < Services.size(); i++)
    {
        if (name == Services[i].getName())
        {
            Services.erase(Services.begin() + i);
        }

    }

   
    ListServices(Services);



}

