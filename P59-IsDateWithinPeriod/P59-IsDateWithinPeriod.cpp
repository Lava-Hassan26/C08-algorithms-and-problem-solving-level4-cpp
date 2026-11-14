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

struct stPeriod
{
    stDate startDate;
    stDate endDate;
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

stPeriod ReadPeriod()
{
    stPeriod period;

    cout << "\nEnter a Period:\n";
    cout << "\nEnter start date:\n";
    period.startDate = ReadDate();
    cout << "\nEnter end date:\n";
    period.endDate = ReadDate();

    return period;
}

bool IsDate1EqualToDate2(stDate date1, stDate date2)
{
    if ((date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day))
        return true;
    return false;
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

bool IsDate1AfterDate2(stDate date1, stDate date2)
{
    return !IsDate1BeforeDate2(date1, date2) && !IsDate1EqualToDate2(date1, date2);
}

bool IsDateWithinPeriod(stPeriod period, stDate date)
{
    if (IsDate1BeforeDate2(date, period.startDate) || IsDate1AfterDate2(date, period.endDate))
        return false;
    return true;
}

int main()
{
    stPeriod period = ReadPeriod();
    cout << "\n\nEnter a date:\n";
    stDate date = ReadDate();
    
    if (IsDateWithinPeriod(period, date))
        cout << "\n\nThe date is within the period\n\n";
    else
        cout << "\n\nThe date is NOT within the period\n\n";
    return 0;
}