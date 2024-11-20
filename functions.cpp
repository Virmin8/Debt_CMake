#include "functions.h"


void ReadFromFile(std::vector<OnlineService> &service)
{
    std::string servicename;
    std::string filename = "UserServices.txt";
    int months;
    int day;
    int month;
    int year;
    double cost;
    std::string  symbol;

    std::ifstream fileIn;
    fileIn.open(filename.c_str());
    if (!fileIn.is_open())
    {
        std::cout << "First Run, Loading Defaults!!\n\n";
        filename = "../Services.txt";
        fileIn.open(filename.c_str());
        if (!fileIn.is_open())
        {
            std::cout << "Error Loading Defaults, Closing Program!!";
            // Needs to be implemented!! iasdiasdiasid

        }

    }
    else
    {
        std::cout << "Resuming from Last Session!!\n\n";
    }
    
        while (fileIn >> servicename >> months >> day >> month >> year >> cost >> symbol)
        {
            OnlineService onlineservices(servicename, months, day, month, year, cost, symbol);
            service.push_back(onlineservices);
        }
    

    if (fileIn.is_open())
    {
        fileIn.close();
    }

}

void WriteToFile(std::vector<OnlineService>& Services)
{
    std::string filename = "../UserServices.txt";
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
    
}

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

