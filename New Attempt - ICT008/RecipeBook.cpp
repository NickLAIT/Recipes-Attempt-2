#include "RecipeBook.h"

RecipeBook::RecipeBook(string t, string a, string i, bool av, string date)
    : title(t), author(a), isbn(i), available(av), addedDate(date), valid(true) {
    validate();
}

RecipeBook::~RecipeBook() {}

string RecipeBook::getIsbn() const {
    return isbn;
}

string RecipeBook::getTitle() const {
    return title;
}

bool RecipeBook::isAvailable() const {
    return available && valid;
}

bool RecipeBook::isValid() const {
    return valid;
}

void RecipeBook::validate() {
    valid = true;
    string problems = "";

    if (author.empty()) {
        problems += "Author error: empty. ";
        valid = false;
    }

    bool allDigits = !isbn.empty();
    for (char c : isbn) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            allDigits = false;
            break;
        }
    }
    if (!allDigits) {
        problems += "ISBN error: must be numeric. ";
        valid = false;
    }

    if (addedDate.length() != 10 ||
        addedDate[4] != '-' ||
        addedDate[7] != '-') {
        problems += "Date error: format should be YYYY-MM-DD. ";
        valid = false;
    }

    if (!problems.empty()) {
        cout << "[Check] \"" << (title.empty() ? "No title" : title)
             << "\": " << problems << "\n";
    }
}

void RecipeBook::show() const {
    if (!valid) {
        cout << "This book has invalid data.\n";
    }
    cout << "Title: " << title << "\n";
    cout << "Author: " << (author.empty() ? "<empty>" : author) << "\n";
    cout << "ISBN: " << isbn << "\n";
    cout << "Available: " << (available ? "Yes" : "No") << "\n";
    cout << "Date added: " << addedDate << "\n";
}

void RecipeBook::borrow() {
    if (!valid) {
        cout << "Cannot borrow \"" << title << "\" because the data is invalid.\n";
        return;
    }
    if (available) {
        available = false;
        cout << "You have borrowed \"" << title << "\".\n";
    } else {
        cout << "Sorry, \"" << title << "\" is already borrowed.\n";
    }
}

void RecipeBook::returnCopy() {
    if (!valid) {
        cout << "Cannot return \"" << title << "\" because the data is invalid.\n";
        return;
    }
    if (!available) {
        available = true;
        cout << "You returned \"" << title << "\".\n";
    } else {
        cout << "This book is already marked as available.\n";
    }
}

PhysicalRecipeBook::PhysicalRecipeBook(string t, string a, string i, bool av,
    string date, string shelf)
    : RecipeBook(t, a, i, av, date), shelfLocation(shelf) {
}

void PhysicalRecipeBook::show() const {
    RecipeBook::show();
    cout << "Shelf location: " << shelfLocation << "\n";
}

DigitalRecipeBook::DigitalRecipeBook(string t, string a, string i, bool av,
    string date, string endDate)
    : RecipeBook(t, a, i, av, date), licenseEndDate(endDate) {
}

void DigitalRecipeBook::show() const {
    RecipeBook::show();
    cout << "License ends on: " << licenseEndDate << "\n";
}

void sortAscendingByTitle(RecipeBook* arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j]->getTitle() > arr[j + 1]->getTitle()) {
                RecipeBook* tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

RecipeLibraryManager::~RecipeLibraryManager() {
    for (RecipeBook* b : books) {
        delete b;
    }
}

void RecipeLibraryManager::addBook(RecipeBook* book) {
    books.push_back(book);
}

RecipeBook* RecipeLibraryManager::findBook(const string& code) {
    for (RecipeBook* b : books) {
        if (b->getIsbn() == code) {
            return b;
        }
    }
    return nullptr;
}

void RecipeLibraryManager::showAvailableBooks() {
    cout << "\n=== Available recipe books ===\n";
    bool any = false;
    for (RecipeBook* b : books) {
        if (b->isAvailable()) {
            b->show();
            cout << "----------------------\n";
            any = true;
        }
    }
    if (!any) {
        cout << "No available books right now.\n";
    }
}

void RecipeLibraryManager::showAllBooks() {
    cout << "\n=== All recipe books (including invalid) ===\n";
    if (books.empty()) {
        cout << "No books in the system.\n";
        return;
    }
    for (RecipeBook* b : books) {
        b->show();
        cout << "----------------------\n";
    }
}
