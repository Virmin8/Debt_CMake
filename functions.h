#define _CRT_SECURE_NO_WARNINGS
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "onlineservice.h"
#include <fstream>
#include <chrono>
#include "TextColour.h"

tm* getTime();

void ReadFromFile(std::vector<OnlineService>&);
void WriteToFile(std::vector<OnlineService>&);

double TotalMonthly(int, std::vector<OnlineService>&);
double TotalYearly(std::vector<OnlineService>&);
double RestMonthly(int, std::vector<OnlineService>&);
double RestYearly(std::vector<OnlineService>&);
void print(int,std::vector<OnlineService>&);
void ListServices(std::vector<OnlineService>&);

void addService(std::vector<OnlineService>&);
void removeService(std::vector<OnlineService>&);




#endif
