#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Abstract base class for all library items
class LibraryItem {
private:
    int id;
    string title;
    string creator;
    int publicationYear;
    bool available;
    string borrowerName;
    string borrowDate;
public:
    LibraryItem();
    LibraryItem(int id, string title, string creator, int publicationYear, bool available = true,
        string borrowerName = "", string borrowDate = "");
    virtual ~LibraryItem();

    // Getters
    int getID() const;
    string getTitle() const;
    string getCreator() const;
    int getYear() const;
    bool isAvailable() const;
    string getBorrowerName() const;
    string getBorrowDate() const;

    // Setters
    void setAvailable(bool a);
    void setBorrowerName(string name);
    void setBorrowDate(string date);

    // Pure virtual functions
    virtual string getType() const = 0;
    virtual void display() const = 0;
    virtual void printToStream(ostream& out) const = 0;
    virtual void saveToFile(ofstream& out) const = 0;
    virtual double calculateLateFee(int overdueDays) const = 0;
};

bool operator<(const LibraryItem& a, const LibraryItem& b);
bool operator==(const LibraryItem& a, const LibraryItem& b);
ostream& operator<<(ostream& out, const LibraryItem& item);
