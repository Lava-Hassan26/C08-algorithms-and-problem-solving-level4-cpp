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

bool IsLastDayInMonth(stDate date)
{
    return date.day == DaysInMonth(date.month, date.year);
}

bool IsLastMonthInYear(stDate date)
{
    return date.month == 12;
}

void IncreaseDateByOne(stDate& date)
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

int PeriodLengthInDays(stPeriod period, bool isEndDayInclude = true)
{
    return DifferenceInDaysBetweenDates(period.startDate, period.endDate, isEndDayInclude);
}

bool IsPeriodsOverlap(stPeriod period1, stPeriod period2)
{
    if (IsDate1BeforeDate2(period2.endDate, period1.startDate)
        || IsDate1AfterDate2(period2.startDate, period1.endDate))
        return false;
    return true;
}

int CountOverlapDays(stPeriod period1, stPeriod period2)
{
    if (!IsPeriodsOverlap(period1, period2))
        return 0;

    int period1Length = PeriodLengthInDays(period1, true);
    int period2Length = PeriodLengthInDays(period2, true);
    int overlapDays = 0;

    if (period1Length < period2Length)
    {
        while (IsDate1BeforeDate2(period1.startDate, period1.endDate))
        {
            if (IsDateWithinPeriod(period2, period1.startDate))
                overlapDays++;
            IncreaseDateByOne(period1.startDate);
        }
    }
    else
    {
        while (IsDate1BeforeDate2(period2.startDate, period2.endDate))
        {
            if (IsDateWithinPeriod(period1, period2.startDate))
                overlapDays++;
            IncreaseDateByOne(period2.startDate);
        }
    }
    return ++overlapDays;
}

int main()
{
    stPeriod period1 = ReadPeriod();
    stPeriod period2 = ReadPeriod();

    cout << "\n\nOverlap Days: " << CountOverlapDays(period1, period2) << endl;
    return 0;
}