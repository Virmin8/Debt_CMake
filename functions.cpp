#include "functions.h"


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
        if ((Services[i].getMonth() == month || Services[i].getEveryfewMonths() == 1) && Services[i].getDay() >= time->tm_mday)
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
    int tmpmonth2 = time->tm_mon + 1;
    int tmpday = time->tm_mday;
    int tmpyear = time->tm_year + 1900;
    

    
    for (int i = 0; i < Services.size(); i++)
    {
        int year = 0;
        int tmpmonth = 0;
        std::string paid = "No";
        SetColour(91);

        if (Services[i].getMonth() == month || Services[i].getEveryfewMonths() == 1)
        {
                if (month < time->tm_mon + 1)
                {
                    SetColour(92);
                    paid = "Yes";
                    if (tmpmonth2 == month)
                    {
                        tmpmonth = 1;
                    }
                }
                else if (month == time->tm_mon + 1 && Services[i].getDay() <= time->tm_mday)
                {
                    SetColour(92);
                    paid = "Yes";
                    if (tmpmonth2 == month)
                    {
                        tmpmonth = 1;
                    }
                    if (Services[i].getEveryfewMonths() == 12)
                    {
                        year = 0;
                        tmpmonth = 0;
                    }
                }
                
          
            Services[i].print(month + tmpmonth, year, paid);
            ResetColour();
           
        }
        
    }
    
}



