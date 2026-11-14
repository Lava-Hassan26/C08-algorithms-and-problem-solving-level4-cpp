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

string ReplaceWordInString(string text, string stringToReplace, string replaceTo)
{
    short pos = text.find(stringToReplace);

    while (pos != std::string::npos) {
        text = text.replace(pos, stringToReplace.length(), replaceTo);
        pos = text.find(stringToReplace);
    }
    return text;
}

string FormatDate(stDate date, string DateFormat = "dd/mm/yyyy")
{
    string formattedStringDate = DateFormat;
    formattedStringDate = ReplaceWordInString(formattedStringDate, "dd", to_string(date.day));
    formattedStringDate = ReplaceWordInString(formattedStringDate, "mm", to_string(date.month));
    formattedStringDate = ReplaceWordInString(formattedStringDate, "yyyy", to_string(date.year));

    return formattedStringDate;
}

int main()
{
    string sDate = ReadString("\nEnter the date dd/mm/yyyy: ");

    stDate date = StringToDate(sDate);

    cout << FormatDate(date) << "\n\n";
    cout << FormatDate(date, "yyyy/dd/mm") << "\n\n";
    cout << FormatDate(date, "mm/dd/yyyy") << "\n\n";
    cout << FormatDate(date, "mm-dd-yyyy") << "\n\n";
    cout << FormatDate(date, "dd/mm/yyyy") << "\n\n";
    cout << FormatDate(date, "Day: dd,Month: mm,Year: yyyy") << "\n\n";

    return 0;
}