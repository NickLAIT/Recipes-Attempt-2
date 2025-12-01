// New Attempt - ICT008.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

class RecipeBook {
private:
    string title;
    string author;
    string isbn;
    bool available;
    string addedDate;

public:
    RecipeBook() {}

    RecipeBook(string t, string a, string i, bool av, string date)
        : title(t), author(a), isbn(i), available(av), addedDate(date) {
    }

    string getIsbn() const {
        return isbn;
    }

    bool isAvailable() const {
        return available;
    }

    void show() const {
        cout << "\nTitle: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
        cout << "Date added: " << addedDate << endl;
    }

    void borrow() {
        if (available) {
            available = false;
            cout << "Nice choice! You just borrowed \"" << title << "\"." << endl;
        }
        else {
            cout << "Oops, \"" << title << "\" is already with someone else." << endl;
        }
    }
};

int findBookByISBN(RecipeBook books[], int count, const string& isbn) {
    for (int i = 0; i < count; i++) {
        if (books[i].getIsbn() == isbn) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int BOOK_COUNT = 7;

    RecipeBook books[BOOK_COUNT] = {
        RecipeBook("From Crook to Cook: Platinum Recipes", "Snoop Dogg", "9781452180329", true, "2025-11-01"),
        RecipeBook("Salt, Fat, Acid, Heat", "Samin Nosrat", "9781476753836", true, "2025-11-01"),
        RecipeBook("The Joy of Cooking", "Irma S. Rombauer", "9781501169717", true, "2025-11-01"),
        RecipeBook("Essentials of Classic Italian Cooking", "Marcella Hazan", "9780394584041", true, "2025-11-01"),
        RecipeBook("The Food Lab", "J. Kenji Lopez-Alt", "9780393081084", true, "2025-11-01"),
        RecipeBook("Baking: From My Home to Yours", "Dorie Greenspan", "9780618443369", true, "2025-11-01"),
        RecipeBook("Mastering the Art of French Cooking Vol. 1", "Julia Child", "9780307292072", true, "2025-11-01")
    };

    cout << "==============================" << endl;
    cout << "  Welcome to My Recipes Hub!  " << endl;
    cout << "==============================" << endl;

    string choice;
    string inputIsbn;

    while (true) {
        cout << "\nWhat do you want to do?" << endl;
        cout << "1 - See all recipe books" << endl;
        cout << "2 - Borrow a book by ISBN" << endl;
        cout << "0 - I'm done, exit" << endl;
        cout << "Your choice: ";
        getline(cin, choice);

        if (choice == "0") {
            cout << "Thanks for visiting the recipe library. See you next time!" << endl;
            break;
        }
        else if (choice == "1") {
            cout << "\nHere are the books in the shelf:" << endl;
            for (int i = 0; i < BOOK_COUNT; i++) {
                books[i].show();
            }
        }
        else if (choice == "2") {
            cout << "Type the ISBN of the book you want (or 0 to cancel): ";
            getline(cin, inputIsbn);

            if (inputIsbn == "0") {
                cout << "No worries, going back to the menu." << endl;
                continue;
            }

            int pos = findBookByISBN(books, BOOK_COUNT, inputIsbn);
            if (pos == -1) {
                cout << "Hmm, could not find a book with that ISBN." << endl;
            }
            else {
                books[pos].borrow();
            }
        }
        else {
            cout << "That option does not exist, try again." << endl;
        }
    }

    return 0;
}
