// work on app version, backend seems pretty much done
// add short term Service
// Add List of Currencies
//Add Password Option
//Change User not working
//add checks when adding and removeing Services

#pragma
#include "functions.h"
#include "onlineservice.h"
#include "program.h"
#include "sqlitefile.h"
#include "Users.h"
#include "admin.h"

int main() {

    tm* now = getTime();
    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;
    char answer;
    std::string response;
    Admin * administrator = new Admin;
    User * user = new User;

    SQLiteClass database;
        

    bool quit = false;
    bool username = false;
    bool change = false;

    std::cout << "The Current Date is :" << day << "/" << month << "/" << year << "\n";

  
        while (!username)
        {
            std::cout << "Please enter Username: ";
            std::cin >> response;
            int admin = database.createUser(response);

            if (admin == 1)
            {
                Admin* tmp = new Admin(response, admin, database);
                *administrator = *tmp;
                username = true;
                delete tmp;
            }
            else if (admin == 0)
            {
                User* tmp = new User(response, admin,database);
                *user = *tmp;
                delete tmp;
                username = true;
            }
            else
                std::cout << "\nUsername does not exist, please ask the Admin to create a user or enter the a valid Username!!\n\n";
        }

        if (administrator->getAdmin() == true)
        {
            while (!quit)
            {
                std::cout << "\nAdd User (1), Remove User (2), List Users (3), List Services (4), Remove Default Service (5), Add Default Service (6), Change User (7), Quit (8): ";
                std::cin >> answer;

                switch (answer)
                {
                case '1':
                    std::cout << "Please add User name: ";
                    std::cin >> response;
                    administrator->adminAddUser(database, response);
                    break;
                case '2':
                    administrator->adminListUsers(database);
                    std::cout << "Please select User name: ";
                    std::cin >> response;
                    administrator->adminRemoveUser(database, response);
                    break;
                case '3':
                    administrator->adminListUsers(database);
                    break;
                case '4':
                    administrator->listServices();
                    break;
                case '5':
                    administrator->removeService(database,administrator->getDefaultServices());
                    break;
                case '6':
                    administrator->customService(database);
                    break;
                case '7':
                    change = true;
                    username = false;
                    break;
                case '8':
                    quit = true;
                    break;
                default:
                    std::cout << "\nInvalid Input!!\n";
                }

            }
            
        }

        if (user->getAdmin() == 0)
        {
            while (!quit)
            {
                std::cout << "\nAdd Service (1), Remove Service (2), List Services (3), Run Program (4), Change User(5), Quit (8): ";
                std::cin >> answer;

                switch (answer)
                {

                case '1':
                    user->addService(database);
                    break;
                case '2':
                    user->removeService(database);
                    break;
                case '3':
                    user->listServices(user->getUsertServices());
                    break;
                case '4':
                    mainProgram(month, user->getUsertServices());
                    break;
                case '5':
                    change = true;
                    username = false;
                    break;
                case '8':
                    quit = true;
                    break;
                default:
                    std::cout << "\nInvalid Input!!\n";
                }

            }

        }
        
    
    delete user;
    delete administrator;
    return 0;
}