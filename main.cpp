#include "include/SearchEngine.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

void displayMenu() {
    cout << "\n=========================================\n";
    cout << "      MINI SEARCH ENGINE CONTROL PANEL    \n";
    cout << "=========================================\n";
    cout << "1. Add New Document\n";
    cout << "2. Search Documents\n";
    cout << "3. View Search Analytics\n";
    cout << "4. Exit\n";
    cout << "=========================================\n";
    cout << "Select an option: ";
}

int main() {
    SearchEngine engine;

    // Pre-populate with some data for convenience
    engine.addDocument("Introduction to AI", "Artificial Intelligence (AI) is intelligence demonstrated by machines, as opposed to the natural intelligence displayed by humans or animals.");
    engine.addDocument("Data Structures", "In computer science, a data structure is a data organization, management, and storage format that enables efficient access and modification.");
    engine.addDocument("Search Engines", "A search engine is a software system that is designed to carry out web searches, which means to search the World Wide Web in a systematic way.");

    int choice;
    string inputBuffer;

    while (true) {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        if (choice == 4) {
            cout << "Exiting Search Engine. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                system("cls");
                string title, content;
                cout << "\n--- Add Document ---\n";
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Content: ";
                getline(cin, content);
                engine.addDocument(title, content);
                cout << "\nPress Enter to return to menu...";
                cin.get();
                break;
            }
			 case 2: {
                 system("cls");
                 cout << "\n--- Search Mode ---\n";
                 cout << "Type a query and press Enter to search.\n";
                 cout << "Type '!q' to return to the main menu.\n";
                 
                 while (true) {
                     cout << "\nSearch > ";
                     string query;
                     getline(cin, query);

                     if (query == "!q") {
                         break;
                     }

                     if (query.empty()) continue;

                     system("cls");
                     cout << "\n--- Search Mode ---\n";
                     cout << "Type '!q' to return to the main menu.\n";
                     cout << "--------------------------------\n";
                     cout << "Results for: '" << query << "'\n\n";

                     engine.searchMultiple(query);
                 }
                 break;
            }
            case 3: {
                system("cls");
                engine.displaySearchStats();
                cout << "\nPress Enter to return to menu...";
                cin.get();
                break;
            }
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
