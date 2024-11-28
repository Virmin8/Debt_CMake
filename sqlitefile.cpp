#include "sqlitefile.h"

SQLiteClass::SQLiteClass() : dbread("../Services.db"), dbwrite("../Services.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    
}

SQLiteClass::~SQLiteClass()
{
    
}

int SQLiteClass::createUser(std::string name)
{
    try
    {

        SQLite::Statement   namequery(dbread, "SELECT Admin FROM Users WHERE Name = (?)");
        namequery.bind(1, name);

        
        while (namequery.executeStep())
        {
            int tmp = namequery.getColumn(0);
            return tmp;
        }


        namequery.reset();

    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

int SQLiteClass::getUserID(std::string name)
{
    int ID = 0;
    try 
    {
        SQLite::Statement   namequery(dbread, "SELECT ID FROM Users WHERE Name = (?)");
        namequery.bind(1, name);

        while (namequery.executeStep())
        {
            ID = namequery.getColumn(0);
            
        }
        namequery.reset();
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    return ID;
}

void SQLiteClass::listUsers()
{
    try
    {

        SQLite::Statement   namequery(dbread, "SELECT Name FROM Users");

        while (namequery.executeStep())
        {
            std::string tmpname = namequery.getColumn(0);
            std::cout << tmpname << std::endl;
        }


        namequery.reset();

    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

}

void SQLiteClass::addUser(std::string name)
{
    try
    {
        bool value = false;
        SQLite::Statement namequery(dbread, "SELECT Name FROM Users");
        SQLite::Statement query(dbwrite, "INSERT INTO Users (Name) VALUES (?)");

        SQLite::Transaction transaction(dbwrite);
        while (namequery.executeStep())
        {
            std::string tmpname = namequery.getColumn(0);
            if (tmpname == name)
            {
                value = true;
            }
        }
        namequery.reset();

        if (value == false)
        {
            query.bind(1, name);
            query.exec();
            query.reset();

            transaction.commit();
        }
        else
            std::cout << "User already Exists!!!\n";
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

}

void SQLiteClass::removeUser(std::string name)
{
    try
    {
        int id;
        SQLite::Statement user(dbread, "SELECT ID FROM Users WHERE Name = (?)");
        user.bind(1, name);

        while (user.executeStep())
        {
            id = user.getColumn(0);
        }


        std::string tmpquery = "DELETE From Users WHERE ID = (?)";
        SQLite::Statement   query(dbwrite, tmpquery);
        SQLite::Statement   queryuser(dbwrite, "DELETE FROM UserServices WHERE UserID = (?)");

        SQLite::Transaction transaction(dbwrite);

        query.bind(1, id);
        queryuser.bind(1, id);

        queryuser.exec();
        queryuser.reset();
        query.exec();
        query.reset();

        transaction.commit();


    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void SQLiteClass::removeService(int userID ,int serviceID)
{
    try
    {
        std::string tmpquery = "DELETE From UserServices WHERE UserID = (?) AND ServiceID = (?)";
        SQLite::Statement   query(dbwrite, tmpquery);

        SQLite::Transaction transaction(dbwrite);

        query.bind(1, userID);
        query.bind(2, serviceID);
        query.exec();
        query.reset();

        transaction.commit();


    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

int SQLiteClass::getLastID()
{
    try
    {
        
        SQLite::Statement   query(dbread, "SELECT ID FROM Services WHERE ID = (SELECT max(ID) FROM Services)");

        while (query.executeStep())
        {
            return query.getColumn(0);

        }


    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void SQLiteClass::ReadFromFile(std::vector<OnlineService>& service)
{
    try
    {
        SQLite::Statement   query(dbread, "SELECT * FROM Services");


        while (query.executeStep())
        {
            OnlineService onlineservices(query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3), query.getColumn(4), query.getColumn(5), query.getColumn(6), query.getColumn(7));
            service.push_back(onlineservices);

        }
        query.reset();
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

}

void SQLiteClass::populateUserService(std::vector<OnlineService>& services, int ID)
{
    try
    {
        SQLite::Statement query(dbread, "SELECT Services.ID, Services.Name,Services.Monthly,Services.Day,Services.Month,Services.Year,Services.Cost,Services.Currency FROM UserServices JOIN Users ON UserServices.UserID = Users.ID JOIN Services ON UserServices.ServiceID = Services.ID WHERE UserID = (?)");
        query.bind(1, ID);

        while (query.executeStep())
        {
            OnlineService onlineservices(query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3), query.getColumn(4), query.getColumn(5), query.getColumn(6), query.getColumn(7));
            services.push_back(onlineservices);

        }
        query.reset();
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

}

void SQLiteClass::addDefaultService(std::string name, int everyfewmonths, int day, int month, int year, double cost, std::string symbol)
{
    try
    {
        SQLite::Statement   query(dbwrite, "INSERT INTO Services (Name,Monthly,Day,Month,Year,Cost,Currency) VALUES (?,?,?,?,?,?,?)");

        SQLite::Transaction transaction(dbwrite);

        query.bind(1, name);
        query.bind(2, everyfewmonths);
        query.bind(3, day);
        query.bind(4, month);
        query.bind(5, year);
        query.bind(6, cost);
        query.bind(7, symbol);

        query.exec();
        query.reset();

        transaction.commit();


    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void SQLiteClass::removeDefaultService(int ID)
{
    try
    {
        std::string tmpquery = "DELETE From Services WHERE ID = (?)";
        SQLite::Statement   query(dbwrite, tmpquery);

        SQLite::Transaction transaction(dbwrite);

        query.bind(1, ID);
        query.exec();
        query.reset();

        transaction.commit();


    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

void SQLiteClass::addService(int userID, int serviceID)
{
    try
    {
        SQLite::Statement   query(dbwrite, "INSERT INTO UserServices (UserID,ServiceID) VALUES (?,?)");

        SQLite::Transaction transaction(dbwrite);

        query.bind(1, userID);
        query.bind(2, serviceID);
        

        query.exec();
        query.reset();

        transaction.commit();


    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

