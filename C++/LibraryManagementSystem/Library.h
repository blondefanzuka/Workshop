#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "LibraryItem.h"
#include "Book.h"
#include "Magazine.h"
#include "DVD.h"
#include "ResearchPaper.h"
#include "Utils.h"
using namespace std;

// Library class manages all items and menu operations
class Library {
private:
    // Map stores items by ID, The key is the item ID
    map<int, unique_ptr<LibraryItem>> items;

    // Finds an item by ID and returns a pointer to it
    LibraryItem* findById(int id);
public:
    void addItem(unique_ptr<LibraryItem> item);
    void newItem();
    void displayItems() const;
    void searchItem();
    void borrowItem();
    void returnItem();
    void deleteItem();
    void sortItems();
    void generateReport();
    void exportReportToFile();
    void saveItemsToFile();
    void loadItemsFromFile();
    void menu();
};
