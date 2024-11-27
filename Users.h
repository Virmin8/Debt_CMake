#ifndef USERS_H
#define USERS_H

#include <string>
#include "onlineservice.h"

class User {
private:
	std::string name;
	bool admin;

public:

	User();
	User(std::string,bool);
	~User();
	void addService();
	void removeService();
	void listUserServices();
	
	std::string getName();
	bool getAdmin();

};
#endif