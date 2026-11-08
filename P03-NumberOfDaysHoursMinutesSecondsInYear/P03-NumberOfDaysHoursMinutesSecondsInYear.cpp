#include <iostream>
#include <string>
#include <limits>

using namespace std;

short ReadNumber(string message)
{
    short number = 0;
    cout << message;
    cin >> number;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "INVALID! Enter a valid number: ";
        cin >> number;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return number;
}

bool IsLeapYear(short year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInYear(short year) 
{
    return IsLeapYear(year) ? 366 : 365;
}

short HoursInYear(short year)
{
    return DaysInYear(year) * 24;
}

int MinutesInYear(short year)
{
    return HoursInYear(year) * 60;
}

int SecondsInYear(short year) 
{
    return MinutesInYear(year) * 60;
}

void PrintNumberOfDaysHoursMinutesSecondsInYear(short year)
{
    cout << "\n----------------------------------------\n";
    cout << "Number of Days    in [" << year << "] = " << DaysInYear(year) << endl;
    cout << "Number of Hours   in [" << year << "] = " << HoursInYear(year) << endl;
    cout << "Number of Minutes in [" << year << "] = " << MinutesInYear(year) << endl;
    cout << "Number of Seconds in [" << year << "] = " << SecondsInYear(year) << endl;
    cout << "----------------------------------------\n";
}

int main() 
{
    short year = ReadNumber("Enter a year: ");
    PrintNumberOfDaysHoursMinutesSecondsInYear(year);

    return 0;
}