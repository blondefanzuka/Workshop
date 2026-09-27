#include "Library.h"

LibraryItem* Library::findById(int id) {
    auto it = items.find(id);
    if (it == items.end()) {
        return nullptr;
    }
    return it->second.get();
}

void Library::addItem(unique_ptr<LibraryItem> item) {
    int id = item->getID();
    if (items.find(id) != items.end()) {
        throw runtime_error("Duplicate ID detected.");
    }
    items[id] = move(item);
}

void Library::newItem() {
    cout << "1. Book" << endl;
    cout << "2. Magazine" << endl;
    cout << "3. DVD" << endl;
    cout << "4. Research Paper" << endl;
    int choice = getInt("Choose item type: ");
    int id = getInt("Enter ID: ");
    string title = getString("Enter title: ");
    string creator = getString("Enter creator: ");
    int year = getInt("Enter publication year: ");
    validateCommonInput(id, title, creator, year);
    if (choice == 1) {
        int pages = getInt("Enter pages: ");
        string genre = getString("Enter genre: ");
        if (pages <= 0) {
            throw runtime_error("Pages must be positive.");
        }
        addItem(make_unique<Book>(id, title, creator, year, true, pages, genre));
    }
    else if (choice == 2) {
        int issueNumber = getInt("Enter issue number: ");
        string month = getString("Enter month: ");
        if (issueNumber <= 0) {
            throw runtime_error("Issue number must be positive.");
        }
        addItem(make_unique<Magazine>(id, title, creator, year, true, issueNumber, month));
    }
    else if (choice == 3) {
        double duration = getDouble("Enter duration: ");
        string ageRating = getString("Enter age rating: ");
        if (duration <= 0) {
            throw runtime_error("Duration must be positive.");
        }
        addItem(make_unique<DVD>(id, title, creator, year, true, duration, ageRating));
    }
    else if (choice == 4) {
        string conference = getString("Enter conference: ");
        string doi = getString("Enter DOI: ");
        addItem(make_unique<ResearchPaper>(id, title, creator, year, true, conference, doi));
    }
    else {
        cout << "Invalid item type." << endl;
        return;
    }
    cout << "Item added successfully." << endl;
}

void Library::displayItems() const {
    if (items.empty()) {
        cout << "No items to display." << endl;
        return;
    }
    for (const auto& pair : items) {
        pair.second->display();
        cout << "-------------------" << endl;
    }
}

void Library::searchItem() {
    if (items.empty()) {
        cout << "No items to search." << endl;
        return;
    }
    cout << "1. Search by ID" << endl;
    cout << "2. Search by title keyword" << endl;
    cout << "3. Search by creator" << endl;
    cout << "4. Search by publication year" << endl;
    cout << "5. Search by item type" << endl;
    int choice = getInt("Choose search option: ");
    bool found = false;
    if (choice == 1) {
        int id = getInt("Enter ID to search: ");
        LibraryItem* item = findById(id);
        if (item == nullptr) {
            cout << "Item not found." << endl;
        }
        else {
            item->display();
        }
        return;
    }
    else if (choice == 2) {
        string keyword = getString("Enter title keyword: ");
        keyword = toLower(keyword);
        for (const auto& pair : items) {
            if (toLower(pair.second->getTitle()).find(keyword) != string::npos) {
                pair.second->display();
                cout << "-------------------" << endl;
                found = true;
            }
        }
    }
    else if (choice == 3) {
        string creator = getString("Enter creator keyword: ");
        creator = toLower(creator);
        for (const auto& pair : items) {
            if (toLower(pair.second->getCreator()).find(creator) != string::npos) {
                pair.second->display();
                cout << "-------------------" << endl;
                found = true;
            }
        }
    }
    else if (choice == 4) {
        int year = getInt("Enter publication year: ");
        for (const auto& pair : items) {
            if (pair.second->getYear() == year) {
                pair.second->display();
                cout << "-------------------" << endl;
                found = true;
            }
        }
    }
    else if (choice == 5) {
        string type = getString("Enter type: ");
        type = toLower(type);
        for (const auto& pair : items) {
            if (toLower(pair.second->getType()) == type) {
                pair.second->display();
                cout << "-------------------" << endl;
                found = true;
            }
        }
    }
    else {
        cout << "Invalid search option." << endl;
        return;
    }
    if (!found) {
        cout << "Item not found." << endl;
    }
}

void Library::borrowItem() {
    int id = getInt("Enter ID to borrow: ");
    LibraryItem* item = findById(id);
    if (item == nullptr) {
        throw runtime_error("Item not found.");
    }
    if (!item->isAvailable()) {
        throw runtime_error("Item is already borrowed.");
    }
    string borrowerName = getString("Enter borrower name: ");
    string borrowDate = getTodayDate();
    item->setAvailable(false);
    item->setBorrowerName(borrowerName);
    item->setBorrowDate(borrowDate);
    cout << "Item borrowed successfully." << endl;
    cout << "Borrow date: " << borrowDate << endl;
    cout << "Loan period: " << LOAN_DAYS << " days" << endl;
}

void Library::returnItem() {
    int id = getInt("Enter ID to return: ");
    LibraryItem* item = findById(id);
    if (item == nullptr) {
        throw runtime_error("Item not found.");
    }
    if (item->isAvailable()) {
        throw runtime_error("Item was not borrowed.");
    }
    string returnDate = getTodayDate();
    int overdueDays = calculateOverdueDays(item->getBorrowDate(), returnDate);
    item->setAvailable(true);
    item->setBorrowerName("");
    item->setBorrowDate("");
    cout << "Item returned successfully." << endl;
    cout << "Return date: " << returnDate << endl;
    cout << "Overdue days: " << overdueDays << endl;
    cout << "Late fee: " << item->calculateLateFee(overdueDays) << " GEL" << endl;
}

void Library::deleteItem() {
    if (items.empty()) {
        cout << "Library is empty." << endl;
        return;
    }
    cout << "1. Delete by ID" << endl;
    cout << "2. Delete by displayed index" << endl;
    int choice = getInt("Choose delete option: ");
    if (choice == 1) {
        int id = getInt("Enter ID to delete: ");
        if (items.erase(id) == 0) {
            cout << "Item not found." << endl;
        }
        else {
            cout << "Item deleted successfully." << endl;
        }
    }
    else if (choice == 2) {
        int index = getInt("Enter displayed index starting from 1: ");
        if (index < 1 || index > static_cast<int>(items.size())) {
            throw runtime_error("Invalid index.");
        }
        auto it = items.begin();
        advance(it, index - 1);
        items.erase(it);
        cout << "Item deleted successfully." << endl;
    }
    else {
        cout << "Invalid delete option." << endl;
    }
}

void Library::sortItems() {
    cout << "1. Sort by title" << endl;
    cout << "2. Sort by year" << endl;
    cout << "3. Sort by type" << endl;
    cout << "4. Sort by availability" << endl;
    int choice = getInt("Choose sorting option: ");
    vector<LibraryItem*> sortedItems;
    for (auto& pair : items) {
        sortedItems.push_back(pair.second.get());
    }
    if (choice == 1) {
        sort(sortedItems.begin(), sortedItems.end(), [](LibraryItem* a, LibraryItem* b) {
            return toLower(a->getTitle()) < toLower(b->getTitle());
            });
    }
    else if (choice == 2) {
        sort(sortedItems.begin(), sortedItems.end(), [](LibraryItem* a, LibraryItem* b) {
            return *a < *b;
            });
    }
    else if (choice == 3) {
        sort(sortedItems.begin(), sortedItems.end(), [](LibraryItem* a, LibraryItem* b) {
            return a->getType() < b->getType();
            });
    }
    else if (choice == 4) {
        sort(sortedItems.begin(), sortedItems.end(), [](LibraryItem* a, LibraryItem* b) {
            return a->isAvailable() > b->isAvailable();
            });
    }
    else {
        cout << "Invalid sort option." << endl;
        return;
    }
    for (LibraryItem* item : sortedItems) {
        item->display();
        cout << "-------------------" << endl;
    }
    cout << "Sorted items displayed." << endl;
}

void Library::generateReport() {
    if (items.empty()) {
        cout << "Library is empty." << endl;
        return;
    }
    int availableCount = 0;
    int bookCount = 0;
    int magazineCount = 0;
    int dvdCount = 0;
    int researchPaperCount = 0;
    LibraryItem* oldest = items.begin()->second.get();
    LibraryItem* newest = items.begin()->second.get();
    for (const auto& pair : items) {
        LibraryItem* item = pair.second.get();
        if (item->isAvailable()) {
            availableCount++;
        }
        if (item->getType() == "Book") bookCount++;
        else if (item->getType() == "Magazine") magazineCount++;
        else if (item->getType() == "DVD") dvdCount++;
        else if (item->getType() == "ResearchPaper") researchPaperCount++;
        if (item->getYear() < oldest->getYear()) oldest = item;
        if (item->getYear() > newest->getYear()) newest = item;
    }
    cout << "Library report" << endl;
    cout << "Total items: " << items.size() << endl;
    cout << "Available items: " << availableCount << endl;
    cout << "Borrowed items: " << items.size() - availableCount << endl;
    cout << "Books: " << bookCount << endl;
    cout << "Magazines: " << magazineCount << endl;
    cout << "DVDs: " << dvdCount << endl;
    cout << "Research Papers: " << researchPaperCount << endl;
    cout << endl << "Oldest Item:" << endl;
    oldest->display();
    cout << endl << "Newest Item:" << endl;
    newest->display();
}

void Library::exportReportToFile() {
    if (items.empty()) {
        cout << "Library is empty." << endl;
        return;
    }
    ofstream out("LibraryReport.txt");
    if (!out) {
        throw runtime_error("Could not open report file.");
    }
    int availableCount = 0;
    int bookCount = 0;
    int magazineCount = 0;
    int dvdCount = 0;
    int researchPaperCount = 0;
    LibraryItem* oldest = items.begin()->second.get();
    LibraryItem* newest = items.begin()->second.get();
    for (const auto& pair : items) {
        LibraryItem* item = pair.second.get();
        if (item->isAvailable()) {
            availableCount++;
        }
        if (item->getType() == "Book") bookCount++;
        else if (item->getType() == "Magazine") magazineCount++;
        else if (item->getType() == "DVD") dvdCount++;
        else if (item->getType() == "ResearchPaper") researchPaperCount++;
        if (item->getYear() < oldest->getYear()) oldest = item;
        if (item->getYear() > newest->getYear()) newest = item;
    }
    out << "Library report" << endl;
    out << "Total items: " << items.size() << endl;
    out << "Available items: " << availableCount << endl;
    out << "Borrowed items: " << items.size() - availableCount << endl;
    out << "Books: " << bookCount << endl;
    out << "Magazines: " << magazineCount << endl;
    out << "DVDs: " << dvdCount << endl;
    out << "Research Papers: " << researchPaperCount << endl;
    out << endl << "Oldest Item:" << endl;
    out << *oldest;
    out << endl << "Newest Item:" << endl;
    out << *newest;
    cout << "Library report exported to LibraryReport.txt." << endl;
}

void Library::saveItemsToFile() {
    ofstream out("SavedItems.txt");
    if (!out) {
        throw runtime_error("Could not open file for saving.");
    }
    for (const auto& pair : items) {
        pair.second->saveToFile(out);
    }
    cout << "Items saved successfully." << endl;
}

void Library::loadItemsFromFile() {
    ifstream in("SavedItems.txt");
    if (!in) {
        return;
    }
    items.clear();
    string line;
    int loadedCount = 0;
    int skippedCount = 0;
    while (getline(in, line)) {
        try {
            if (line.empty()) {
                continue;
            }
            vector<string> parts;
            string part = "";
            for (char ch : line) {
                if (ch == '|') {
                    parts.push_back(part);
                    part = "";
                }
                else {
                    part += ch;
                }
            }
            parts.push_back(part);
            if (parts.size() != 10) {
                throw runtime_error("Invalid number of fields.");
            }
            string type = parts[0];
            int id = stoi(parts[1]);
            string title = parts[2];
            string creator = parts[3];
            int year = stoi(parts[4]);
            bool available = stoi(parts[5]);
            string borrowerName = parts[6];
            string borrowDate = parts[7];
            validateCommonInput(id, title, creator, year);
            if (!available) {
                if (borrowerName.empty() || borrowDate.empty()) {
                    throw runtime_error("Borrowed item must have borrower name and borrow date.");
                }
                calculateOverdueDays(borrowDate, getTodayDate());
            }
            if (type == "Book") {
                int pages = stoi(parts[8]);
                string genre = parts[9];
                if (pages <= 0 || genre.empty()) {
                    throw runtime_error("Invalid book data.");
                }
                addItem(make_unique<Book>(id, title, creator, year, available, pages, genre, borrowerName, borrowDate));
            }
            else if (type == "Magazine") {
                int issueNumber = stoi(parts[8]);
                string month = parts[9];
                if (issueNumber <= 0 || month.empty()) {
                    throw runtime_error("Invalid magazine data.");
                }
                addItem(make_unique<Magazine>(id, title, creator, year, available, issueNumber, month, borrowerName, borrowDate));
            }
            else if (type == "DVD") {
                double duration = stod(parts[8]);
                string ageRating = parts[9];
                if (duration <= 0 || ageRating.empty()) {
                    throw runtime_error("Invalid DVD data.");
                }
                addItem(make_unique<DVD>(id, title, creator, year, available, duration, ageRating, borrowerName, borrowDate));
            }
            else if (type == "ResearchPaper") {
                string conference = parts[8];
                string doi = parts[9];
                if (conference.empty() || doi.empty()) {
                    throw runtime_error("Invalid research paper data.");
                }
                addItem(make_unique<ResearchPaper>(id, title, creator, year, available, conference, doi, borrowerName, borrowDate));
            }
            else {
                throw runtime_error("Unknown item type.");
            }
            loadedCount++;
        }
        catch (const exception&) {
            skippedCount++;
        }
    }
    cout << "Items loaded successfully." << endl;
    cout << "Loaded records: " << loadedCount << endl;
    cout << "Skipped invalid records: " << skippedCount << endl;
}

void Library::menu() {
    int choice;
    do {
        cout << "Zuka's library menu" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Display Items" << endl;
        cout << "3. Search Item" << endl;
        cout << "4. Borrow Item" << endl;
        cout << "5. Return Item" << endl;
        cout << "6. Delete Item" << endl;
        cout << "7. Sort Items" << endl;
        cout << "8. Generate Report" << endl;
        cout << "9. Save Items" << endl;
        cout << "10. Load Items" << endl;
        cout << "11. Export Report to File" << endl;
        cout << "12. Save and Exit" << endl;
        choice = getInt("Enter choice: ");
        try {
            switch (choice) {
            case 1: newItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: borrowItem(); break;
            case 5: returnItem(); break;
            case 6: deleteItem(); break;
            case 7: sortItems(); break;
            case 8: generateReport(); break;
            case 9: saveItemsToFile(); break;
            case 10: loadItemsFromFile(); break;
            case 11: exportReportToFile(); break;
            case 12:
                saveItemsToFile();
                cout << "Goodbye." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } 
    while (choice != 12);
}
