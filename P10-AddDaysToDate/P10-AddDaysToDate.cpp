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

short DayOrderOfWeek(short day, short month, short year)
{
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + 12 * a - 2;
    short d = (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
    return d;
}

short DaysFromYearStart(short day, short month, short year)
{
    short days = 0;
    for (short i = 1; i < month; i++)
        days += DaysInMonth(i, year);
    days += day;

    return days;
}

stDate GetDate(short dayOrderInYear, short year)
{
    short counter = 0;
    while (dayOrderInYear > 0)
    {
        counter++;
        short currentMonthDays = DaysInMonth(counter, year);
        if (dayOrderInYear > currentMonthDays)
            dayOrderInYear -= DaysInMonth(counter, year);
        else
            break;
    }
    stDate date;
    date.year = year;
    date.month = counter;
    date.day = dayOrderInYear;

    return date;
}

stDate AddDaysToDate(stDate date, int daysToAdd)
{
    int totalDays = daysToAdd + DaysFromYearStart(date.day, date.month, date.year);
    date.month = 1;

    while (true)
    {
        short daysInMonth = DaysInMonth(date.month, date.year);
        if (totalDays > daysInMonth)
        {
            totalDays -= daysInMonth;
            date.month++;
            if (date.month > 12)
            {
                date.month = 1;
                date.year++;
            }
        }
        else
        {
            date.day = totalDays;
            break;
        }
    }
    return date;
}

int main()
{
    stDate date = ReadDate();
    int daysToAdd = ReadNumber("Enter Days To Add: ");
    date = AddDaysToDate(date, daysToAdd);

    cout << "\n\nDate After Adding Days: " << to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year) << endl;

    return 0;
}