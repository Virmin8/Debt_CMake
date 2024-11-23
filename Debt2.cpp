// work on app version, backend seems pretty much done
// add short term Service
// Add Users, which link to seperate Services
// Add List of Currencies
// Move SQL to seperate Class

#pragma
#include "functions.h"
#include "onlineservice.h"
#include "program.h"

int main() {
    
    tm* now = getTime();
    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;
    char answer;
    std::string response;

    std::vector<OnlineService> Services;
  
    
    bool quit = false;


    ReadFromFile(Services);
    
    std::cout << "The Current Date is :" << day << "/" << month << "/" << year << "\n";

    while (!quit)
    {
        std::cout << "\nAdd User (1), Remove User (2), Add Service (3), Remove Service (4), List Users (5), List Services (6), Run Program (7), Quit (8): ";
        std::cin >> answer;

        switch (answer)
        {
        case '1':
            std::cout << "Please add User name: ";
            std::cin >> response;
            addUser(response);
            break;
        case '2':
            listUsers();
            std::cout << "Please select User name: ";
            std::cin >> response;
            removeUser(response);
            break;
        case '3':
            addService(Services);
            break;
        case '4':
            removeService(Services);
            break;
        case '5':
            listUsers();
            break;
        case '6':
            ListServices(Services);
            break;
        case '8':
            quit = true;
            break;
        case '7':
            mainProgram(month, Services);
            break;
        default:
            std::cout << "\nInvalid Input!!\n";
        }

    }
     
    return 0;
}