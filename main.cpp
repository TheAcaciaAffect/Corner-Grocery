#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

#include "GroceryItem.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static const string INPUT_FILE = "CS210_Project_Three_Input_File.txt";
static const string BACKUP_FILE = "frequency.dat";

string ToLowerLocal(const string& text) {
    string result;
    result.reserve(text.size());
    for (char ch : text) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }
    return result;
}

int FindItemIndex(const vector<GroceryItem>& items, const string& keyNameLower) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].GetKeyName() == keyNameLower) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

vector<GroceryItem> LoadFrequenciesFromFile(const string& filename) {
    vector<GroceryItem> items;
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: Could not open input file: " << filename << endl;
        return items; // returns empty; caller can handle gracefully
    }

    string word;
    while (inFile >> word) {
        string key = ToLowerLocal(word);

        int idx = FindItemIndex(items, key);
        if (idx >= 0) {
            items[idx].Increment();
        }
        else {
            items.push_back(GroceryItem(word));
        }
    }

    return items;
}

void WriteBackupFile(const vector<GroceryItem>& items, const string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Warning: Could not create backup file: " << filename << endl;
        return;
    }

    for (const GroceryItem& item : items) {
        outFile << item.GetDisplayName() << " " << item.GetQuantity() << endl;
    }
}

int GetValidatedMenuChoice() {
    int choice = 0;

    while (true) {
        cout << "\n========== Corner Grocer Menu ==========\n";
        cout << "1. Look up an item frequency\n";
        cout << "2. Print all item frequencies\n";
        cout << "3. Print histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";

        if (cin >> choice && choice >= 1 && choice <= 4) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid input. Please enter a number from 1 to 4.\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void MenuOptionOne() {
    vector<GroceryItem> items = LoadFrequenciesFromFile(INPUT_FILE);
    WriteBackupFile(items, BACKUP_FILE); // keep backup current in case file changed

    if (items.empty()) {
        cout << "No data loaded. Check that the input file exists and is not empty.\n";
        return;
    }

    cout << "Enter the item you want to search for: ";
    string userItem;
    std::getline(cin, userItem);

    string key = ToLowerLocal(userItem);
    int idx = FindItemIndex(items, key);

    if (idx >= 0) {
        cout << items[idx].GetDisplayName() << " was purchased "
            << items[idx].GetQuantity() << " time(s).\n";
    }
    else {
        cout << userItem << " was purchased 0 time(s).\n";
    }
}

void MenuOptionTwo() {
    vector<GroceryItem> items = LoadFrequenciesFromFile(INPUT_FILE);
    WriteBackupFile(items, BACKUP_FILE);

    if (items.empty()) {
        cout << "No data loaded. Check that the input file exists and is not empty.\n";
        return;
    }

    cout << "\n----- Item Frequencies -----\n";
    for (const GroceryItem& item : items) {
        cout << item.GetDisplayName() << " " << item.GetQuantity() << endl;
    }
}

void MenuOptionThree() {
    vector<GroceryItem> items = LoadFrequenciesFromFile(INPUT_FILE);
    WriteBackupFile(items, BACKUP_FILE);

    if (items.empty()) {
        cout << "No data loaded. Check that the input file exists and is not empty.\n";
        return;
    }

    cout << "\n----- Histogram -----\n";
    for (const GroceryItem& item : items) {
        cout << item.GetDisplayName() << " ";
        for (int i = 0; i < item.GetQuantity(); ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

// ---------- Main Program ----------

int main() {
    // Required: create backup file at program start (no user intervention).
    vector<GroceryItem> startupItems = LoadFrequenciesFromFile(INPUT_FILE);
    WriteBackupFile(startupItems, BACKUP_FILE);

    int choice = 0;
    do {
        choice = GetValidatedMenuChoice();

        switch (choice) {
        case 1:
            MenuOptionOne();
            break;
        case 2:
            MenuOptionTwo();
            break;
        case 3:
            MenuOptionThree();
            break;
        case 4:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            // Should never happen due to validation
            cout << "Unexpected menu option.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}