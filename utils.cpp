#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "data.cpp"

using namespace std;

bool openFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return false;
    }
    else
    {
        return true;
    }
}

vector<string> split(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
};

bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return true;
    }
    return false;
}

bool validateDate(const string &date)
{
    vector<string> parts = split(date, '-');
    if (parts.size() != 3)
    {
        cout << "Date format should be dd-mm-yyyy";
        return false;
    }

    int day = stoi(parts[0]);
    int month = stoi(parts[1]);
    int year = stoi(parts[2]);

    if (month < 1 || month > 12)
    {
        cout << "Invalid months passed";
        return false;
    }
    if (year < 1)
    {
        cout << "Invalid years passed";
        return false;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
    {
        cout << "For leap years Feb has 29 days";
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1])
    {
        cout << "Invalid days passed";
        return false;
    }

    return true;
}

bool addItem(Item item)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile)
    {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }
    outputFile << item.id << "," << item.name << "," << item.quantity << "," << item.regDate << endl;
}

void listItems()
{
    vector<Item> items;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Could not open the file " << filename << endl;
        exit(0);
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        Item item;

        if (getline(iss, token, ','))
        {
            item.id = stoi(token);
        }
        if (getline(iss, token, ','))
        {
            item.name = token;
        }
        if (getline(iss, token, ','))
        {
            item.quantity = stoi(token);
        }
        if (getline(iss, token, ','))
        {
            item.regDate = token;
        }

        items.push_back(item);
    }
    file.close();
    for (const auto &item : items)
    {
        cout << "Item ID: " << item.id
             << "\t Item Name: " << item.name
             << "\t Quantity: " << item.quantity
             << "\t Reg Date: " << item.regDate << endl;
    }
}

void help()
{
    cout << "---------------------------------------------------" << endl;
    cout << "*                 Command syntaxes                *" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "itemadd <item_id> <item_name> <quantity> <registration_date> - Adds an item\n";
    cout << "itemslist - Lists all items\n";
    cout << "help - Shows this help message\n";
}

string toLowerCase(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void processCommand(const string &input)
{
    istringstream iss(input);
    string command;
    iss >> command;

    if (toLowerCase(command) == "itemadd")
    {
        Item item;
        string dateString;

        if (iss >> item.id >> item.name >> item.quantity >> dateString)
        {
            if (!validateDate(dateString))
            {
                help();
            }
            item.regDate = dateString;
            addItem(item);
            cout << "Adding item: " << item.id << ", Name: " << item.name << ", Quantity: " << item.quantity << ", Date: " << item.regDate << endl;
        }
        else
        {
            cerr << "Invalid arguments for itemadd command.\n";
        }
    }
    else if (toLowerCase(command) == "itemslist")
    {
        cout << "Listing items...\n";
        listItems();
    }
    else if (toLowerCase(command) == "help")
    {
        help();
    }
    else if (toLowerCase(command) == "exit")
    {
        cout << "Exiting program..." << endl;
        exit(0);
    }
    else
    {
        cerr << "Unknown command.\n";
        help();
    }
}