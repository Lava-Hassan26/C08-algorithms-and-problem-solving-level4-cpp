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

 //P19
void IncreaseDateByXDays(stDate& date, int days)
{
    for (int i = 0; i < days; i++)
        IncreaseDateByOneDay(date);
}

//20
void IncreaseDateByOneWeek(stDate& date)
{
    IncreaseDateByXDays(date, 7);
}

//21
void IncreaseDateByXWeeks(stDate& date, int weeks)
{
    for (int i = 0; i < weeks; i++)
        IncreaseDateByOneWeek(date);
}

//P22
void IncreaseDateByOneMonth(stDate& date)
{
    if (date.month == 12)
    {
        date.month = 1;
        date.year++;
    }
    else
        date.month++;

    short maxDaysInCurrentMonth = DaysInMonth(date.month, date.year);
    if (date.day > maxDaysInCurrentMonth)
        date.day = maxDaysInCurrentMonth;
}

//P23
void IncreaseDateByXMonths(stDate& date, short months)
{
    for (short i = 0; i < months; i++)
        IncreaseDateByOneMonth(date);
}

//P24
void IncreaseDateByOneYear(stDate& date)
{
    date.year++;
    if (date.month == 2 && date.day == 29 && !IsLeapYear(date.year))
        date.day = 28;
}

//P25
void IncreaseDateByXYears(stDate& date, short years)
{
    for (short i = 0; i < years; i++)
        IncreaseDateByOneYear(date);
}

//P26
void IncreaseDateByOneDecade(stDate& date)
{
    IncreaseDateByXYears(date, 10);
}

//P27
void IncreaseDateByXDecades(stDate& date, short decades)
{
    for (short i = 0; i < decades; i++)
        IncreaseDateByOneDecade(date);
}

//P28
void IncreaseDateByOneCentury(stDate& date)
{
    IncreaseDateByXYears(date, 100);
}

//P29
void IncreaseDateByXCentury(stDate& date, short centuries)
{
    for (short i = 0; i < centuries; i++)
        IncreaseDateByOneCentury(date);
}

//P30
void IncreaseDateByOneMillennium(stDate& date)
{
    IncreaseDateByXYears(date, 1000);
}

//P31
void IncreaseDateByXMillenniums(stDate& date, short millenniums)
{
    for (short i = 0; i < millenniums; i++)
        IncreaseDateByOneMillennium(date);
}

string DateToString(stDate date)
{
    return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

int main() 
{
    stDate date = ReadDate();

    cout << "\n\n------------------- Results -------------------\n";

    IncreaseDateByOneDay(date);
    cout << "01. After adding one day       : " << DateToString(date) << endl;

    IncreaseDateByXDays(date, 10);
    cout << "02. After adding 10 days       : " << DateToString(date) << endl;

    IncreaseDateByOneWeek(date);
    cout << "03. After adding one week      : " << DateToString(date) << endl;

    IncreaseDateByXWeeks(date, 2);
    cout << "04. After adding 2 weeks       : " << DateToString(date) << endl;

    IncreaseDateByOneMonth(date);
    cout << "05. After adding one month     : " << DateToString(date) << endl;

    IncreaseDateByXMonths(date, 3);
    cout << "06. After adding 3 months      : " << DateToString(date) << endl;

    IncreaseDateByOneYear(date);
    cout << "07. After adding one year      : " << DateToString(date) << endl;

    IncreaseDateByXYears(date, 5);
    cout << "08. After adding 5 years       : " << DateToString(date) << endl;

    IncreaseDateByOneDecade(date);
    cout << "09. After adding one decade    : " << DateToString(date) << endl;

    IncreaseDateByXDecades(date, 2);
    cout << "10. After adding 2 decades     : " << DateToString(date) << endl;

    IncreaseDateByOneCentury(date);
    cout << "11. After adding one century   : " << DateToString(date) << endl;

    IncreaseDateByXCentury(date, 2);
    cout << "12. After adding 2 centuries   : " << DateToString(date) << endl;

    IncreaseDateByOneMillennium(date);
    cout << "13. After adding one millennium: " << DateToString(date) << endl;

    IncreaseDateByXMillenniums(date, 1);
    cout << "14. After adding 1 millennium  : " << DateToString(date) << endl;

    return 0;
}