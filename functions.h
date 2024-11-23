#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "onlineservice.h"
#include <fstream>
#include <chrono>
#include "TextColour.h"
#include "sqlitefile.h"

tm* getTime();

void ReadFromFile(std::vector<OnlineService>&);
void WriteToFile(std::vector<OnlineService>&);

double TotalMonthly(int, std::vector<OnlineService>&);
double TotalYearly(std::vector<OnlineService>&);
double RestMonthly(int, std::vector<OnlineService>&);
double RestYearly(std::vector<OnlineService>&);
void print(int,std::vector<OnlineService>&);
void ListServices(std::vector<OnlineService>&);

void addServiceList(std::vector<OnlineService>&,SQLiteClass&);
void removeService(std::vector<OnlineService>& ,SQLiteClass& );

void addUser(std::string);
void removeUser(std::string, SQLiteClass&);
void listUsers();

#endif
