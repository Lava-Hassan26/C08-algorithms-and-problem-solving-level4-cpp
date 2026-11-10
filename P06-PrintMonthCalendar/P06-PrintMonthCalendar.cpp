#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

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

short DayOrderOfWeek(short day, short month, short year) 
{
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + 12 * a - 2;
    short d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
    return d;
}

string GetMonthName(short month) 
{
    string arrMonthName[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    return arrMonthName[month - 1];
}

void PrintMonthCalendar(short month, short year)
{
    short dayOrderOfWeek = DayOrderOfWeek(1, month, year);
    short numberOfDaysInMonth = DaysInMonth(month, year);
    cout << "\n   _________________{" << GetMonthName(month) << "}_________________\n\n";
    cout << "   Sun   Mon   Tue   Wed   Thu   Fri   Sat   \n";

    for (short i = 0; i < dayOrderOfWeek; i++) 
        cout << "      ";

    for (short i = 1; i <= numberOfDaysInMonth; i++)
    {
        printf("%6d", i);
        if ((i + dayOrderOfWeek) % 7 == 0)
            cout << endl;
    }
    cout << "\n   _______________________________________\n";
}

int main() {
    short year = ReadYear();
    short month = ReadMonth();
    PrintMonthCalendar(month, year);

    return 0;
}