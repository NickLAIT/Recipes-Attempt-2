#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// ================= Base class =================
class RecipeBook {
protected:
    string title;
    string author;
    string isbn;
    bool available;
    string addedDate;
    bool valid;

public:
    RecipeBook(string t, string a, string i, bool av, string date)
        : title(t), author(a), isbn(i), available(av), addedDate(date), valid(true) {
        validate();
    }

    virtual ~RecipeBook() {}

    string getIsbn() const { return isbn; }
    string getTitle() const { return title; }
    bool isAvailable() const { return available && valid; }
    bool isValid() const { return valid; }

    void validate() {
        valid = true;
        string problems = "";

        // Author not empty
        if (author.empty()) {
            problems += "Author error: empty. ";
            valid = false;
        }

        // ISBN numeric
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

        // Date format YYYY-MM-DD
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

    virtual void show() const {
        if (!valid) {
            cout << "This book has invalid data.\n";
        }
        cout << "Title: " << title << "\n";
        cout << "Author: " << (author.empty() ? "<empty>" : author) << "\n";
        cout << "ISBN: " << isbn << "\n";
        cout << "Available: " << (available ? "Yes" : "No") << "\n";
        cout << "Date added: " << addedDate << "\n";
    }

    void borrow() {
        if (!valid) {
            cout << "Cannot borrow \"" << title << "\" because the data is invalid.\n";
            return;
        }
        if (available) {
            available = false;
            cout << "You have borrowed \"" << title << "\".\n";
        }
        else {
            cout << "Sorry, \"" << title << "\" is already borrowed.\n";
        }
    }

    void returnCopy() {
        if (!valid) {
            cout << "Cannot return \"" << title << "\" because the data is invalid.\n";
            return;
        }
        if (!available) {
            available = true;
            cout << "You returned \"" << title << "\".\n";
        }
        else {
            cout << "This book is already marked as available.\n";
        }
    }
};

// ============== Physical recipe book ==============
class PhysicalRecipeBook : public RecipeBook {
    string shelfLocation;
public:
    PhysicalRecipeBook(string t, string a, string i, bool av,
        string date, string shelf)
        : RecipeBook(t, a, i, av, date), shelfLocation(shelf) {
    }

    void show() const override {
        RecipeBook::show();
        cout << "Shelf location: " << shelfLocation << "\n";
    }
};

// ============== Digital recipe book ==============
class DigitalRecipeBook : public RecipeBook {
    string licenseEndDate;
public:
    DigitalRecipeBook(string t, string a, string i, bool av,
        string date, string endDate)
        : RecipeBook(t, a, i, av, date), licenseEndDate(endDate) {
    }

    void show() const override {
        RecipeBook::show();
        cout << "License ends on: " << licenseEndDate << "\n";
    }
};

// ============== Simple bubble sort helper ==============
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

// ============== Manager ==============
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

    RecipeBook* findBook(const string& code) {
        for (RecipeBook* b : books) {
            if (b->getIsbn() == code) {
                return b;
            }
        }
        return nullptr;
    }

    void showAvailableBooks() {
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

    void showAllBooks() {
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
};

// ============== main ==============
int main() {
    RecipeLibraryManager manager;

    // Correct books (used also for sort tests)
    PhysicalRecipeBook* good1 = new PhysicalRecipeBook(
        "From Crook to Cook: Platinum Recipes", "Snoop Dogg",
        "9781452180329", true, "2025-11-01", "R1");

    PhysicalRecipeBook* good2 = new PhysicalRecipeBook(
        "Salt, Fat, Acid, Heat", "Samin Nosrat",
        "9781476753836", true, "2025-11-01", "A2");

    PhysicalRecipeBook* good3 = new PhysicalRecipeBook(
        "The Joy of Cooking", "Irma S. Rombauer",
        "9781501169717", true, "2025-11-01", "B3");

    manager.addBook(good1);
    manager.addBook(good2);
    manager.addBook(good3);

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

    // Incorrect books only for validation messages (not part of sorting)
    manager.addBook(new PhysicalRecipeBook(
        "From Crook to Cook (Bad)", "Snoop Dogg",
        "9781452X80329", true, "11-01-2025", "Z1"));   // wrong ISBN and date

    manager.addBook(new PhysicalRecipeBook(
        "Salt, Fat, Acid, Heat (Bad)", "",
        "9781476753836", true, "2025/11/01", "Z2"));   // empty author, wrong date

    manager.addBook(new DigitalRecipeBook(
        "The Joy of Cooking (Bad)", "Irma S. Rombauer",
        "ABC501169717", true, "2025-11", "2030-01-01")); // wrong ISBN and date

    cout << "=============================\n";
    cout << " Welcome to My Recipes Hub!\n";
    cout << "=============================\n";

    string choice;
    string isbn;

    while (true) {
        cout << "\nMain menu\n";
        cout << "1 - Show available books\n";
        cout << "2 - Borrow a book (by ISBN)\n";
        cout << "3 - Return a book (by ISBN)\n";
        cout << "4 - Sorting tests (submenu)\n";
        cout << "5 - Show all books (for checking)\n";
        cout << "0 - Exit\n";
        cout << "Choice: ";
        getline(cin, choice);

        if (choice == "0") {
            cout << "Thanks for visiting the recipe library. Goodbye!\n";
            break;
        }
        else if (choice == "1") {
            manager.showAvailableBooks();
        }
        else if (choice == "2") {
            cout << "Enter ISBN to borrow: ";
            getline(cin, isbn);
            RecipeBook* book = manager.findBook(isbn);
            if (!book) {
                cout << "No recipe book with that ISBN.\n";
            }
            else {
                book->borrow();
            }
        }
        else if (choice == "3") {
            cout << "Enter ISBN to return: ";
            getline(cin, isbn);
            RecipeBook* book = manager.findBook(isbn);
            if (!book) {
                cout << "No recipe book with that ISBN.\n";
            }
            else {
                book->returnCopy();
            }
        }
        else if (choice == "4") {
            // sorting submenu using only the three correct books
            while (true) {
                cout << "\nSorting submenu\n";
                cout << "1 - Ascending order array\n";
                cout << "2 - Descending order array\n";
                cout << "3 - Mixed order array\n";
                cout << "0 - Back to main menu\n";
                cout << "Choice: ";
                string sortChoice;
                getline(cin, sortChoice);

                if (sortChoice == "0") {
                    break;
                }
                else if (sortChoice == "1") {
                    // Ascending added: already A–Z by title
                    RecipeBook* asc[3] = { good1, good2, good3 };
                    cout << "\nArray 1 (ascending):\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << asc[i]->getTitle() << "\n";
                    sortAscendingByTitle(asc, 3);
                    
                }
                else if (sortChoice == "2") {
                    // Descending added: reverse alphabetical order
                    RecipeBook* desc[3] = { good3, good2, good1 };
                    cout << "\nArray 2 (descending):\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << desc[i]->getTitle() << "\n";
                    sortAscendingByTitle(desc, 3);
                    
                }
                else if (sortChoice == "3") {
                    // Mixed added
                    RecipeBook* mixed[3] = { good2, good1, good3 };
                    cout << "\nArray 3 (mixed):\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << mixed[i]->getTitle() << "\n";
                    sortAscendingByTitle(mixed, 3);
                    
                }
                else {
                    cout << "Not a valid sorting option.\n";
                }
            }
        }
        else if (choice == "5") {
            manager.showAllBooks();
        }
        else {
            cout << "That option is not on the menu, try again.\n";
        }
    }

    return 0;
}

