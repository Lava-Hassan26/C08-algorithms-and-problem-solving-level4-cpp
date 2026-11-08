#include <iostream>
#include <string>
#include <limits>

using namespace std;

long long ReadNumber(string message) {
    long long number = 0;
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

string NumberToText(long long number)
{
    if (number == 0)
        return "";

    if (number >= 1 && number < 20) {
        string numWord[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
        return numWord[number] + " ";
    }

    if (number >= 20 && number < 100) {
        string numWord[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
        return numWord[number / 10] + " " + NumberToText(number % 10);
    }

    if (number >= 100 && number < 1000) {
        return NumberToText(number / 100) + "Hundred " + NumberToText(number % 100);
    }

    if (number >= 1000 && number < 1000000) {
        return NumberToText(number / 1000) + "Thousand " + NumberToText(number % 1000);
    }

    if (number >= 1000000 && number < 1000000000) {
        return NumberToText(number / 1000000) + "Million " + NumberToText(number % 1000000);
    }

    if (number >= 1000000000 && number < 1000000000000LL) {
        return NumberToText(number / 1000000000) + "Billion " + NumberToText(number % 1000000000);
    }

    return "Number is too large!";
}

int main() {
    long long num = ReadNumber("Enter a number: ");

    cout << NumberToText(num) << endl;

    return 0;
}