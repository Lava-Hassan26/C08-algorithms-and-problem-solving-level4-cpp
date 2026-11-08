#include <iostream>
#include <string>
#include <limits>

using namespace std;

short ReadNumber(string message) {
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

int main()
{
    short year = ReadNumber("Enter a year: ");

    if (IsLeapYear(year))
        cout << "\nIt is a leap year.\n";
    else
        cout << "\nIt NOT is a leap year.\n";

    return 0;
}