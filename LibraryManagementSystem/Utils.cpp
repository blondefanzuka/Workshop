#include "Utils.h"

const int MIN_YEAR = 1450;
const int LOAN_DAYS = 14;

// Converts text to lowercase for case-insensitive searching
string toLower(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return tolower(c);
        });
    return text;
}

// Gets the current year from the system clock
int getCurrentYear() {
    time_t now = time(nullptr);
    tm local;
    localtime_s(&local, &now);
    return local.tm_year + 1900;
}

// Adds a zero before one digit months/days
string twoDigits(int number) {
    if (number < 10) {
        return "0" + to_string(number);
    }
    return to_string(number);
}

// Gets today's date from the computer and stores it
string getTodayDate() {
    time_t now = time(nullptr);
    tm local;
    localtime_s(&local, &now);
    int year = local.tm_year + 1900;
    int month = local.tm_mon + 1;
    int day = local.tm_mday;
    return to_string(year) + "-" + twoDigits(month) + "-" + twoDigits(day);
}

// Date conversion
int dateToDays(int year, int month, int day) {
    return year * 365 + month * 30 + day;
}

// Reads a date written as YYYY-MM-DD
bool readDate(string date, int& year, int& month, int& day) {
    if (date.length() != 10) {
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    try {
        year = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day = stoi(date.substr(8, 2));
    }
    catch (const exception&) {
        return false;
    }
    if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    return true;
}

// Calculates how many days late the item is after the loan period
int calculateOverdueDays(string borrowDate, string returnDate) {
    int by, bm, bd, ry, rm, rd;
    if (!readDate(borrowDate, by, bm, bd)) {
        throw runtime_error("Invalid borrow date.");
    }
    if (!readDate(returnDate, ry, rm, rd)) {
        throw runtime_error("Invalid return date.");
    }
    int borrowedDays = dateToDays(ry, rm, rd) - dateToDays(by, bm, bd);
    if (borrowedDays < 0) {
        throw runtime_error("Return date cannot be before borrow date.");
    }
    if (borrowedDays <= LOAN_DAYS) {
        return 0;
    }
    return borrowedDays - LOAN_DAYS;
}

// Reads an integer and throws an exception if the input is invalid
int getInt(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw runtime_error("Invalid number input.");
    }
    cin.ignore(10000, '\n');
    return value;
}

// Reads a decimal number and throws an exception if the input is invalid
double getDouble(const string& prompt) {
    double value;
    cout << prompt;
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw runtime_error("Invalid number input.");
    }
    cin.ignore(10000, '\n');
    return value;
}

// Reads a non empty string from the user
string getString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    if (value.empty()) {
        throw runtime_error("Input cannot be empty.");
    }
    return value;
}

// Validates fields that every library item has
void validateCommonInput(int id, string title, string creator, int year) {
    if (id <= 0) {
        throw runtime_error("ID must be positive.");
    }
    if (title.empty()) {
        throw runtime_error("Title cannot be empty.");
    }
    if (creator.empty()) {
        throw runtime_error("Creator cannot be empty.");
    }
    if (year < MIN_YEAR || year > getCurrentYear()) {
        throw runtime_error("Publication year is not reasonable.");
    }
}
