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

bool IsLastDayInMonth(stDate date)
{
    return date.day == DaysInMonth(date.month, date.year);
}

bool IsLastMonthInYear(stDate date)
{
    return date.month == 12;
}

void IncreaseDateByOneDay(stDate& date)
{
    if (IsLastDayInMonth(date))
    {
        if (IsLastMonthInYear(date))
        {
            date.day = 1;
            date.month = 1;
            date.year++;
        }
        else
        {
            date.day = 1;
            date.month++;
        }
    }
    else
        date.day++;
}

bool IsDate1BeforeDate2(stDate date1, stDate date2)
{
    if (date1.year < date2.year)
        return true;
    if ((date1.year <= date2.year) && (date1.month < date2.month))
        return true;
    if ((date1.year <= date2.year) && (date1.month <= date2.month) && (date1.day < date2.day))
        return true;
    return false;
}

bool IsDate1EqualToDate2(stDate date1, stDate date2)
{
    if ((date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day))
        return true;
    return false;
}

bool IsWeekEnd(stDate date)
{
    short dayOrder = DayOrderOfWeek(date.day, date.month, date.year);
    return dayOrder == 0 || dayOrder == 6;
}

bool IsBusinessDay(stDate date)
{
    return !IsWeekEnd(date);
}

short CalculateVacationDays(stDate startDate, stDate endDate)
{
    if(IsDate1EqualToDate2(startDate, endDate))
        return 0;

    if (!IsDate1BeforeDate2(startDate, endDate))
    {
        cout << "\nInvalid! must start date be before end date\n";
        return 0;
    }
    short vacationDays = 0;

    while (IsDate1BeforeDate2(startDate,endDate))
    {
        if (IsBusinessDay(startDate))
        {
            vacationDays++;
        }
        IncreaseDateByOneDay(startDate);
    }
    if (IsBusinessDay(endDate))
        vacationDays++;

    return vacationDays;
}

int main()
{
    cout << "\nVacation Start Date:\n";
    stDate startDate = ReadDate();

    cout << "\nVacation End Date:\n";
    stDate endDate = ReadDate();

    cout << "\nActual Vacation Days: " << CalculateVacationDays(startDate, endDate) << endl;
  
    return 0;
}