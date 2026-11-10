#include <iostream>
#include <string>
#include <limits>

using namespace std;

short ReadNumber(string message)
{
    short number = 0;
    cout << message;
    cin >> number;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "INVALID! Enter a valid number: ";
        cin >> number;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return number;
}

short ReadYear()
{
    short year = ReadNumber("Enter a year: ");
    return year;
}

short ReadMonth()
{
    short month = 0;
    month = ReadNumber("Enter a month: ");

    while (month < 1 || month>12)
    {
        cout << "\nINVALID! Month must be between 1 and 12.\n";
        month = ReadNumber("Enter a month: ");
    }
    return month;
}

short ReadDay()
{
    short day = 0;
    day = ReadNumber("Enter a day: ");

    while (day < 1 || day>31)
    {
        cout << "\nINVALID! Day must be between 1 and 31.\n";
        day = ReadNumber("Enter a day: ");
    }
    return day;
}

short DayOrderOfWeek(short day, short month, short year)
{
    float a = (14 - month) / 12;
    float y = year - a;
    float m = month + 12 * a - 2;
    short k = day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12);

    return k % 7;
}

string GetDayName(short day, short month, short year)
{
    string arrDayName[] = {"Sunday", "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };

    return arrDayName[DayOrderOfWeek(day, month, year)];
}

int main()
{
    short year = ReadYear();
    short month = ReadMonth();
    short day = ReadDay();

    cout << "\nDate     : " << day << "/" << month << "/" << year << endl;
    cout << "Day Order: " << DayOrderOfWeek(day, month, year) << endl;
    cout << "Day Name : " << GetDayName(day, month, year) << endl;

    return 0;
}