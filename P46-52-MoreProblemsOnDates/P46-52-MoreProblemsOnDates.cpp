#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <limits>
#include <ctime>
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

short DaysInYear(short year)
{
    return IsLeapYear(year) ? 366 : 365;
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

short DaysFromYearStart(short day, short month, short year)
{
    short days = 0;
    for (short i = 1; i < month; i++)
        days += DaysInMonth(i, year);
    days += day;

    return days;
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

short DayOrderOfWeek(short day, short month, short year)
{
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + 12 * a - 2;
    short d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
    return d;
}

string GetDayName(short day, short month, short year)
{
    string arrDayName[] = { "Sunday", "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };

    return arrDayName[DayOrderOfWeek(day, month, year)];
}

stDate GetSystemDate()
{
    stDate date;
    time_t t = time(0);
    tm* now = localtime(&t);

    date.year = now->tm_year + 1900;
    date.month = now->tm_mon + 1;
    date.day = now->tm_mday;

    return date;
}

string DateToString(stDate date)
{
    return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

//P46
void PrintTodayDate()
{
    stDate date = GetSystemDate();
    string dayName = GetDayName(date.day, date.month, date.year);
    cout << "Today's Date is: " << dayName << ", " << DateToString(date) << endl;
}

//P47
bool IsEndOfWeek(stDate date)
{
    return DayOrderOfWeek(date.day, date.month, date.year) == 5;
}

//P48
bool IsWeekEnd(stDate date)
{
    short dayOrder = DayOrderOfWeek(date.day, date.month, date.year);
    return dayOrder == 0 || dayOrder == 6;
}

//P49
bool IsBusinessDay(stDate date)
{
    return !IsWeekEnd(date);
}

//50
short DaysUntilTheEndOfWeek(stDate date)
{
    return 6 - DayOrderOfWeek(date.day, date.month, date.year);
}

//P51
short DaysUntilTheEndOfMonth(stDate date)
{
    return DaysInMonth(date.month, date.year) - date.day;
}

//P52
short DaysUntilTheEndOfYear(stDate date)
{
    return DaysInYear(date.year) - DaysFromYearStart(date.day, date.month, date.year);
}

int main()
{
    stDate date = GetSystemDate();

    PrintTodayDate();

    if (IsEndOfWeek(date))
        cout << "\nIt is the end of week\n";
    else
        cout << "\nIt is NOT the end of week\n";

    if (IsWeekEnd(date))
        cout << "\nIt is weekend\n";
    else
        cout << "\nIt is NOT weekend\n";

    if (IsBusinessDay(date))
        cout << "\nIt is business day\n";
    else
        cout << "\nIt is NOT business day\n";

    cout << "\nRemaining days until the end of week: " << DaysUntilTheEndOfWeek(date);
    cout << "\nRemaining days until the end of month: " << DaysUntilTheEndOfMonth(date);
    cout << "\nRemaining days until the end of year: " << DaysUntilTheEndOfYear(date);
    return 0;
}