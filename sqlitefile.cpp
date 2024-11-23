#include "sqlitefile.h"

SQLiteClass::SQLiteClass() : dbread("../Services.db"), dbwrite("../Services.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    
}

SQLiteClass::~SQLiteClass()
{
    
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

void SQLiteClass::removeDatabase(std::string name, std::string table)
{
    try
    {
        std::string tmpquery = "DELETE From " + table + " WHERE Name = (?)";
        SQLite::Statement   query(dbwrite, tmpquery);

        SQLite::Transaction transaction(dbwrite);

        query.bind(1, name);
        query.exec();
        query.reset();

        transaction.commit();


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
        SQLite::Statement   query(dbread, "SELECT * FROM Test");


        while (query.executeStep())
        {
            OnlineService onlineservices(query.getColumn(0), query.getColumn(1), query.getColumn(2), query.getColumn(3), query.getColumn(4), query.getColumn(5), query.getColumn(6));
            service.push_back(onlineservices);

        }
        query.reset();
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

}

void SQLiteClass::addService(std::string name, int everyfewmonths, int day, int month, int year, double cost, std::string symbol)
{
    try
    {
        SQLite::Statement   query(dbwrite, "INSERT INTO Test (Name,Monthly,Day,Month,Year,Cost,Currency) VALUES (?,?,?,?,?,?,?)");

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