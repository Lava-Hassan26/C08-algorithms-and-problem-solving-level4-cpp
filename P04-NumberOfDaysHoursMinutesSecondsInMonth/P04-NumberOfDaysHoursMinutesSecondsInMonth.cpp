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

bool IsLeapYear(short year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInMonth(short year, short month)
{
    short daysOfMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2)
        return IsLeapYear(year) ? 29 : 28;
    return daysOfMonth[month - 1];
}

short HoursInMonth(short year, short month)
{
    return DaysInMonth(year, month) * 24;
}

int MinutesInMonth(short year, short month)
{
    return HoursInMonth(year, month) * 60;
}

int SecondsInMonth(short year, short month)
{
    return MinutesInMonth(year, month) * 60;
}

void PrintNumberOfDaysHoursMinutesSecondsInMonth(short year, short month)
{
    cout << "\n----------------------------------------\n";
    cout << "Number of Days    in [" << month << "] = " << DaysInMonth(year, month) << endl;
    cout << "Number of Hours   in [" << month << "] = " << HoursInMonth(year, month) << endl;
    cout << "Number of Minutes in [" << month << "] = " << MinutesInMonth(year, month) << endl;
    cout << "Number of Seconds in [" << month << "] = " << SecondsInMonth(year, month) << endl;
    cout << "----------------------------------------\n";
}

int main()
{
    short year = ReadYear();
    short month = ReadMonth();
    PrintNumberOfDaysHoursMinutesSecondsInMonth(year, month);

    return 0;
}