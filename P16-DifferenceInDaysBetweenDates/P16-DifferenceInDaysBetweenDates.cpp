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

int DifferenceInDaysBetweenDates(stDate date1, stDate date2, bool isEndDayInclude = true)
{
    if (IsDate1EqualToDate2(date1, date2)) 
        return 0;

    if (!IsDate1BeforeDate2(date1, date2))
    {
        cout << "\nInvalid! must date1 be before date2\n";
        return 0;
    }
    int diffDays = 0;

    while (true)
    {
        if (date1.year < date2.year)
        {
            diffDays += IsLeapYear(date1.year) ? 366 : 365;
            date1.year++;
        }
        else
            break;
    }
    diffDays += DaysFromYearStart(date2.day, date2.month, date2.year) - DaysFromYearStart(date1.day, date1.month, date1.year);
    return isEndDayInclude ? ++diffDays : diffDays;
}

int main()
{
    cout << "\nEnter date1:\n";
    stDate date1 = ReadDate();

    cout << "\nEnter date2:\n";
    stDate date2 = ReadDate();

    cout << "\nDifference in days between the two dates= " << DifferenceInDaysBetweenDates(date1, date2, false);
    cout << "\nDifference in days between the two dates (Including end day)= " << DifferenceInDaysBetweenDates(date1, date2) << endl;

    return 0;
}