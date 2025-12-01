// New Attempt - ICT008.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class
class RecipeBook {
protected:
    string title;
    string author;
    string isbn;
    bool available;
    string addedDate;

public:
    RecipeBook(string t, string a, string i, bool av, string date)
        : title(t), author(a), isbn(i), available(av), addedDate(date) {
    }

    virtual ~RecipeBook() {}

    string getIsbn() const {
        return isbn;
    }

    bool isAvailable() const {
        return available;
    }

    virtual void show() const {
        cout << "\nTitle: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
        cout << "Date added: " << addedDate << endl;
    }

    void borrow() {
        if (available) {
            available = false;
            cout << "Nice choice! You have borrowed \"" << title << "\"." << endl;
        }
        else {
            cout << "Sorry, \"" << title << "\" is already with someone else." << endl;
        }
    }

    void returnCopy() {
        if (!available) {
            available = true;
            cout << "Thanks! You returned \"" << title << "\"." << endl;
        }
        else {
            cout << "This book was already marked as available." << endl;
        }
    }
};

// Physical recipe book
class PhysicalRecipeBook : public RecipeBook {
    string shelfLocation;
public:
    PhysicalRecipeBook(string t, string a, string i, bool av,
        string date, string shelf)
        : RecipeBook(t, a, i, av, date), shelfLocation(shelf) {
    }

    void show() const override {
        RecipeBook::show();
        cout << "Shelf location: " << shelfLocation << endl;
    }
};

// Digital recipe book
class DigitalRecipeBook : public RecipeBook {
    string licenseEndDate;
public:
    DigitalRecipeBook(string t, string a, string i, bool av,
        string date, string endDate)
        : RecipeBook(t, a, i, av, date), licenseEndDate(endDate) {
    }

    void show() const override {
        RecipeBook::show();
        cout << "License ends on: " << licenseEndDate << endl;
    }
};

// Manager
class RecipeLibraryManager {
    vector<RecipeBook*> books;

public:
    ~RecipeLibraryManager() {
        for (RecipeBook* b : books) {
            delete b;
        }
    }

    void addBook(RecipeBook* book) {
        books.push_back(book);
    }

    RecipeBook* findBook(const string& isbn) {
        for (RecipeBook* b : books) {
            if (b->getIsbn() == isbn) {
                return b;
            }
        }
        return nullptr;
    }

    void showAvailableBooks() {
        cout << "\n=== Books you can borrow right now ===" << endl;
        for (RecipeBook* b : books) {
            if (b->isAvailable()) {
                b->show();
                cout << "-----------------------------" << endl;
            }
        }
    }
};

int main() {
    RecipeLibraryManager manager;

    // Add physical and digital recipe books
    manager.addBook(new PhysicalRecipeBook(
        "From Crook to Cook: Platinum Recipes", "Snoop Dogg",
        "9781452180329", true, "2025-11-01", "R1"));

    manager.addBook(new PhysicalRecipeBook(
        "Salt, Fat, Acid, Heat", "Samin Nosrat",
        "9781476753836", true, "2025-11-01", "A2"));

    manager.addBook(new PhysicalRecipeBook(
        "The Joy of Cooking", "Irma S. Rombauer",
        "9781501169717", true, "2025-11-01", "B3"));

    manager.addBook(new DigitalRecipeBook(
        "Essentials of Classic Italian Cooking", "Marcella Hazan",
        "9780394584041", true, "2025-11-01", "2026-12-31"));

    manager.addBook(new DigitalRecipeBook(
        "The Food Lab", "J. Kenji Lopez-Alt",
        "9780393081084", true, "2025-11-01", "2027-01-01"));

    manager.addBook(new PhysicalRecipeBook(
        "Baking: From My Home to Yours", "Dorie Greenspan",
        "9780618443369", true, "2025-11-01", "A5"));

    manager.addBook(new DigitalRecipeBook(
        "Mastering the Art of French Cooking Vol. 1", "Julia Child",
        "9780307292072", true, "2025-11-01", "2028-05-05"));

    cout << "==============================" << endl;
    cout << "  Welcome to My Recipes Hub!  " << endl;
    cout << "==============================" << endl;

    string choice;
    string isbn;

    while (true) {
        cout << "\nWhat do you want to do now?" << endl;
        cout << "1 - Show books that are available" << endl;
        cout << "2 - Borrow a book (by ISBN)" << endl;
        cout << "3 - Return a book (by ISBN)" << endl;
        cout << "0 - I'm full, leave the kitchen" << endl;
        cout << "Your choice: ";
        getline(cin, choice);

        if (choice == "0") {
            cout << "Thanks for hanging out in the recipe library. See you next time!" << endl;
            break;
        }
        else if (choice == "1") {
            manager.showAvailableBooks();
        }
        else if (choice == "2") {
            cout << "Type the ISBN of the book you want: ";
            getline(cin, isbn);
            RecipeBook* book = manager.findBook(isbn);
            if (book == nullptr) {
                cout << "Hmm, no book with that ISBN here." << endl;
            }
            else {
                book->borrow();
            }
        }
        else if (choice == "3") {
            cout << "Type the ISBN of the book you are returning: ";
            getline(cin, isbn);
            RecipeBook* book = manager.findBook(isbn);
            if (book == nullptr) {
                cout << "That ISBN does not match any book in this library." << endl;
            }
            else {
                book->returnCopy();
            }
        }
        else {
            cout << "That option is not on the menu, try again." << endl;
        }
    }

    return 0;
}
