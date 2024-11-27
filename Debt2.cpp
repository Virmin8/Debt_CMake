// work on app version, backend seems pretty much done
// add short term Service
// Add Users, which link to seperate Services
// Add List of Currencies
//Add Password Option

#pragma
#include "functions.h"
#include "onlineservice.h"
#include "program.h"
#include "sqlitefile.h"
#include "Users.h"

int main() {

    tm* now = getTime();
    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;
    char answer;
    std::string response;
    Admin administrator;
    User user;

    std::vector<OnlineService> defaultServices;

    SQLiteClass database;
        

    bool quit = false;
    bool username = false;
    bool change = false;

    database.ReadFromFile(defaultServices);


    std::cout << "The Current Date is :" << day << "/" << month << "/" << year << "\n";

   
         while (!username)
        {
            std::cout << "Please enter Username: ";
            std::cin >> response;
            int admin = database.createUser(response);
            change = false;

            if (admin == 1)
            {
                Admin tmp (response, admin);
                administrator = tmp;
                username = true;
               std::cout<< administrator.getAdmin();
            }
            else if (admin == 0)
            {
                User tmp(response, admin);
                user = tmp;
                username = true;
            }
            else
                std::cout << "\nUsername does not exist, please ask the Admin to create a user or enter the a valid Username!!\n\n";
        }

        if (administrator.getAdmin() == true)
        {
            while (!quit)
            {
                std::cout << "\nAdd User (1), Remove User (2), List Users (3), List Services (4), Change User (5), Quit (8): ";
                std::cin >> answer;

                switch (answer)
                {
                case '1':
                    std::cout << "Please add User name: ";
                    std::cin >> response;
                    administrator.adminAddUser(database, response);
                    break;
                case '2':
                    administrator.adminListUsers(database);
                    std::cout << "Please select User name: ";
                    std::cin >> response;
                   administrator.adminRemoveUser(database,response);
                    break;
                case '3':
                   administrator.adminListUsers(database);
                    break;
                case '4':
                    ListServices(defaultServices);
                    break;
                case '5' :
                    change = true;
                    break;
                case '8':
                    quit = true;
                    break;
                default:
                    std::cout << "\nInvalid Input!!\n";
                }

            }
        }

        if (user.getAdmin() == 0)
        {
            while (!quit)
            {
                std::cout << "\nAdd Service (1), Remove Service (2), List Services (3), Run Program (4), Change User(5), Quit (8): ";
                std::cin >> answer;

                switch (answer)
                {

                case '1':
                    addServiceList(defaultServices, database);
                    break;
                case '2':
                    removeService(defaultServices, database);
                    break;
                case '3':
                    ListServices(defaultServices);
                    break;
                case '4':
                    mainProgram(month, defaultServices);
                    break;
                case '5':
                    change = true;
                    break;
                case '8':
                    quit = true;
                    break;
                default:
                    std::cout << "\nInvalid Input!!\n";
                }

            }

        }

    return 0;
}