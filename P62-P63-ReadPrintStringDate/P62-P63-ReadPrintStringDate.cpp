#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct stDate
{
    short year = 0;
    short month = 0;
    short day = 0;
};

string ReadString(string message)
{
    string text = "";
    cout << message;
    getline(cin, text);
    return text;
}

vector<string> SplitString(string text, string delim = " ")
{
    vector<string> vWords;
    string word = "";
    short pos = 0;
    pos = text.find(delim);

    while ((pos) != std::string::npos)
    {
        word = text.substr(0, pos);
        if (word != "")
            vWords.push_back(word);
        text.erase(0, pos + delim.length());
        pos = text.find(delim);
    }
    if (text != "")
        vWords.push_back(text);
    return vWords;
}

stDate StringToDate(string sDate)
{
    stDate date;
    vector <string> vDate = SplitString(sDate, "/");

    date.day = stoi(vDate[0]);
    date.month = stoi(vDate[1]);
    date.year = stoi(vDate[2]);

    return date;
}

string DateToString(stDate date)
{
    return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

void PrintDate(stDate date)
{
    cout << "\n\nDay  : " << date.day;
    cout << "\nMonth: " << date.month;
    cout << "\nYear : " << date.year;
}

int main()
{
    string sDate = ReadString("\nEnter the date dd/mm/yyyy: ");
    stDate date = StringToDate(sDate);

    PrintDate(date);
    cout << "\n\nDate in String: " << DateToString(date) << endl;

    return 0;
}