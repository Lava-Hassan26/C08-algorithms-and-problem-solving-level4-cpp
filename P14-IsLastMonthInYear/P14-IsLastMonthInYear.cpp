#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct stDate
{
    short year = 0;
    short month = 0;
    short day = 0;
};

short ReadNumber(string message)
{
    short number = 0;
    cout << message;
    cin >> number;

    while (cin.fail())
    {
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

    while (month < 1 || month > 12)
    {
        cout << "\nINVALID! Month must be between 1 and 12.\n";
        month = ReadNumber("Enter a month: ");
    }
    return month;
}

bool IsLeapYear(short year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInMonth(short month, short year)
{
    if (month < 1 || month > 12)
        return 0;
    short daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2)
        return IsLeapYear(year) ? 29 : 28;

    return daysOfMonth[month - 1];
}

short ReadDay(short month, short year)
{
    short day = 0;
    short maxDaysInMonth = DaysInMonth(month, year);
    day = ReadNumber("Enter a day: ");

    while (day < 1 || day>maxDaysInMonth)
    {
        cout << "\nINVALID! Day for month " << month << " must be between 1 and " << maxDaysInMonth << endl;
        day = ReadNumber("Enter a day: ");
    }
    return day;
}

stDate ReadDate()
{
    stDate date;
    date.year = ReadYear();
    date.month = ReadMonth();
    date.day = ReadDay(date.month, date.year);
    return date;
}

bool IsLastMonthInYear(stDate date)
{
    return date.month == 12;
}

int main()
{
    cout << "\nEnter a date\n";
    stDate date1 = ReadDate();

    if (IsLastMonthInYear(date1))
        cout << "\nIt is the last month in the year\n";
    else
        cout << "\nIt is NOT the last month in the year\n";

    return 0;
}