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

//P32
void DecreaseDateByOneDay(stDate& date)
{
    if (date.day == 1)
    {
        if (date.month == 1)
        {
            date.day = 31;
            date.month = 12;
            date.year--;
        }
        else
        {
            date.month--;
            date.day = DaysInMonth(date.month, date.year);
        }
    }
    else
        date.day--;
}

//P33
void DecreaseDateByXDays(stDate& date, int days)
{
    for (int i = 0; i < days; i++)
        DecreaseDateByOneDay(date);
}

//34
void DecreaseDateByOneWeek(stDate& date)
{
    DecreaseDateByXDays(date, 7);
}

//35
void DecreaseDateByXWeeks(stDate& date, int weeks)
{
    for (int i = 0; i < weeks; i++)
        DecreaseDateByOneWeek(date);
}

//P36
void DecreaseDateByOneMonth(stDate& date)
{
    if (date.month == 1)
    {
        date.month = 12;
        date.year--;
    }
    else
        date.month--;

    short maxDaysInCurrentMonth = DaysInMonth(date.month, date.year);
    if (date.day > maxDaysInCurrentMonth)
        date.day = maxDaysInCurrentMonth;
}

//P37
void DecreaseDateByXMonths(stDate& date, short months)
{
    for (short i = 0; i < months; i++)
        DecreaseDateByOneMonth(date);
}

//P38
void DecreaseDateByOneYear(stDate& date)
{
    date.year--;
    if (date.month == 2 && date.day == 29 && !IsLeapYear(date.year))
        date.day = 28;
}

//P39
void DecreaseDateByXYears(stDate& date, short years)
{
    for (short i = 0; i < years; i++)
        DecreaseDateByOneYear(date);
}

//P40
void DecreaseDateByOneDecade(stDate& date)
{
    DecreaseDateByXYears(date, 10);
}

//P41
void DecreaseDateByXDecades(stDate& date, short decades)
{
    for (short i = 0; i < decades; i++)
        DecreaseDateByOneDecade(date);
}

//P42
void DecreaseDateByOneCentury(stDate& date)
{
    DecreaseDateByXYears(date, 100);
}

//P43
void DecreaseDateByXCentury(stDate& date, short centuries)
{
    for (short i = 0; i < centuries; i++)
        DecreaseDateByOneCentury(date);
}

//P44
void DecreaseDateByOneMillennium(stDate& date)
{
    DecreaseDateByXYears(date, 1000);
}

//P45
void DecreaseDateByXMillenniums(stDate& date, short millenniums)
{
    for (short i = 0; i < millenniums; i++)
        DecreaseDateByOneMillennium(date);
}

string DateToString(stDate date)
{
    return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

int main()
{
    stDate date = ReadDate();

    cout << "\n\n------------------- Results -------------------\n";
    DecreaseDateByOneDay(date);
    cout << "01. After decreasing one day       : " << DateToString(date) << endl;

    DecreaseDateByXDays(date, 10);
    cout << "02. After decreasing 10 days       : " << DateToString(date) << endl;

    DecreaseDateByOneWeek(date);
    cout << "03. After decreasing one week      : " << DateToString(date) << endl;

    DecreaseDateByXWeeks(date, 2);
    cout << "04. After decreasing 2 weeks       : " << DateToString(date) << endl;

    DecreaseDateByOneMonth(date);
    cout << "05. After decreasing one month     : " << DateToString(date) << endl;

    DecreaseDateByXMonths(date, 3);
    cout << "06. After decreasing 3 months      : " << DateToString(date) << endl;

    DecreaseDateByOneYear(date);
    cout << "07. After decreasing one year      : " << DateToString(date) << endl;

    DecreaseDateByXYears(date, 5);
    cout << "08. After decreasing 5 years       : " << DateToString(date) << endl;

    DecreaseDateByOneDecade(date);
    cout << "09. After decreasing one decade    : " << DateToString(date) << endl;

    DecreaseDateByXDecades(date, 2);
    cout << "10. After decreasing 2 decades     : " << DateToString(date) << endl;

    DecreaseDateByOneCentury(date);
    cout << "11. After decreasing one century   : " << DateToString(date) << endl;

    DecreaseDateByXCentury(date, 2);
    cout << "12. After decreasing 2 centuries   : " << DateToString(date) << endl;

    DecreaseDateByOneMillennium(date);
    cout << "13. After decreasing one millennium: " << DateToString(date) << endl;

    DecreaseDateByXMillenniums(date, 1);
    cout << "14. After decreasing 1 millennium  : " << DateToString(date) << endl;

    return 0;
}