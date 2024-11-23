#include "program.h"


void mainProgram(int month, std::vector<OnlineService>& Services)
{
    std::string r;
    double total = 0.00;
    int count = 0;
    int tmp = 0;

    std::cout << "\nList of Services for the Month: \n";
    print(month, Services);
    total = RestMonthly(month, Services);

    if (count == 0)
    {
        std::cout << "\nTotal Cost for the rest of the month: " << total << "\n";
        total = RestYearly(Services);
        std::cout << "Total Cost for the rest of the year: " << total << "\n";
        count++;
    }


    total = TotalMonthly(month, Services);
    std::cout << std::endl << "Total Cost for the month: " << total << "\n";
    total = TotalYearly(Services);
    std::cout << "Total Cost for the year: " << total << "\n\n";

    total = 0.00;

        

    do{
    std::cout << "\nPlease enter which month you would like to see the costs for (1-12) or Options (O): ";
    std::cin >> r;
    std::cout << "\n";
    std::stringstream ss;
        
    ss << r;
    ss >> tmp;
   
    
    if (tmp > 0 && tmp < 13)
    {
        print(tmp, Services);
    }
    else if (r != "O" && r != "o")
        std::cout << "Invalid Input, Please Enter Valid Input\n";
    } while (r != "O" && r != "o" || (tmp < 0 && tmp > 13));

    
}