#ifndef ONLINESERVICE_H
#define ONLINESERVICE_H

#include <vector>
#include <string>
#include <iostream>
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"
#include <cstring>

class OnlineService
{
private:
    std::string name;
    int everyfemonths;
    int day;
    int month;
    int year;
    double cost;
    double currencyConverter(std::string _currency);
    std::string symbol;
    void rollOver();
    int length;
    double convertedCost;

    
public:
    OnlineService(std::string, int, int, int, int, double , std::string);
    ~OnlineService();

    int getDay();
    int getEveryfewMonths();
    int getMonth();
    double getCost();
    int getYear();
    std::string getName();
    std::string  getSymbol();
    int getLength();
    double getConvertedCost();
    void setDay(int);
    void setEveryfewMonths(int);
    void setMonth(int);
    void setCost(double);
    void setYear(int);
    void setName(std::string);
    void setLength(int);
    

    void print();
    void print(int, int, std::string);
};

#endif