#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <ctime>
using namespace std;

extern const int MIN_YEAR;
extern const int LOAN_DAYS;

string toLower(string text);
int getCurrentYear();
string twoDigits(int number);
string getTodayDate();
int dateToDays(int year, int month, int day);
bool readDate(string date, int& year, int& month, int& day);
int calculateOverdueDays(string borrowDate, string returnDate);
int getInt(const string& prompt);
double getDouble(const string& prompt);
string getString(const string& prompt);
void validateCommonInput(int id, string title, string creator, int year);
