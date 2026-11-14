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

bool IsValidDate(stDate date) {
    // 1. Validate month bounds first
    if (date.month < 1 || date.month > 12)
        return false;

    // 2. Validate basic day bounds (1 to 31)
    if (date.day < 1 || date.day > 31)
        return false;

    // 3. Validate day against the specific month and year 
    // (This automatically covers February, leap years, and 30/31-day months)
    short daysInMonth = DaysInMonth(date.month, date.year);
    if (date.day > daysInMonth)
        return false;

    return true;
}

int main()
{
    return 0;
}