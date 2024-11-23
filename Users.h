#ifndef USERS_H
#define USERS_H

#include <string>

class User {
private:
	std::string name;
	bool admin;

public:

	User(std::string, bool);
	~User();
	addService();
	removeService();
	
	
};
#endif