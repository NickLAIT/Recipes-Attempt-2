#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class RecipeBook {
protected:
    string title;
    string author;
    string isbn;
    bool available;
    string addedDate;
    bool valid;

public:
    RecipeBook(string t, string a, string i, bool av, string date);
    virtual ~RecipeBook();

    string getIsbn() const;
    string getTitle() const;
    bool isAvailable() const;
    bool isValid() const;

    void validate();
    virtual void show() const;
    void borrow();
    void returnCopy();
};

class PhysicalRecipeBook : public RecipeBook {
    string shelfLocation;
public:
    PhysicalRecipeBook(string t, string a, string i, bool av,
        string date, string shelf);
    void show() const override;
};

class DigitalRecipeBook : public RecipeBook {
    string licenseEndDate;
public:
    DigitalRecipeBook(string t, string a, string i, bool av,
        string date, string endDate);
    void show() const override;
};

void sortAscendingByTitle(RecipeBook* arr[], int size);

class RecipeLibraryManager {
    vector<RecipeBook*> books;

public:
    ~RecipeLibraryManager();
    void addBook(RecipeBook* book);
    RecipeBook* findBook(const string& code);
    void showAvailableBooks();
    void showAllBooks();
};

#endif
