#include <iostream>
#include <string>
#include "RecipeBook.h"
using namespace std;

int main() {
    RecipeLibraryManager manager;

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

    manager.addBook(new PhysicalRecipeBook(
        "From Crook to Cook (Bad)", "Snoop Dogg",
        "9781452X80329", true, "11-01-2025", "Z1"));

    manager.addBook(new PhysicalRecipeBook(
        "Salt, Fat, Acid, Heat (Bad)", "",
        "9781476753836", true, "2025/11/01", "Z2"));

    manager.addBook(new DigitalRecipeBook(
        "The Joy of Cooking (Bad)", "Irma S. Rombauer",
        "ABC501169717", true, "2025-11", "2030-01-01"));

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
            } else {
                book->borrow();
            }
        }
        else if (choice == "3") {
            cout << "Enter ISBN to return: ";
            getline(cin, isbn);
            RecipeBook* book = manager.findBook(isbn);
            if (!book) {
                cout << "No recipe book with that ISBN.\n";
            } else {
                book->returnCopy();
            }
        }
        else if (choice == "4") {
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
                    RecipeBook* asc[3] = { good1, good2, good3 };
                    cout << "\nArray 1 (ascending added) before sort:\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << asc[i]->getTitle() << "\n";
                    sortAscendingByTitle(asc, 3);
                    cout << "Array 1 after sort:\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << asc[i]->getTitle() << "\n";
                }
                else if (sortChoice == "2") {
                    RecipeBook* desc[3] = { good3, good2, good1 };
                    cout << "\nArray 2 (descending added) before sort:\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << desc[i]->getTitle() << "\n";
                    sortAscendingByTitle(desc, 3);
                    cout << "Array 2 after sort (ascending result):\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << desc[i]->getTitle() << "\n";
                }
                else if (sortChoice == "3") {
                    RecipeBook* mixed[3] = { good2, good1, good3 };
                    cout << "\nArray 3 (mixed added) before sort:\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << mixed[i]->getTitle() << "\n";
                    sortAscendingByTitle(mixed, 3);
                    cout << "Array 3 after sort (ascending result):\n";
                    for (int i = 0; i < 3; ++i)
                        cout << "- " << mixed[i]->getTitle() << "\n";
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
