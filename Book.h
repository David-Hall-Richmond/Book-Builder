#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include <vector>
#include "Page.h"
#include "Index.h"

/* Book class representing a collection of the pages of the provided text along with an Index with facility to convert
to HTML. The book class manages execution and organization of the the collection*/
class Book{
public:

    Book(std::string newTitle);
    Page getPage(int index);
    void addPage(std::string newPage);
    void print();
    int getNumPages();
    void createIndex();
    void createPageHTMLS();
    void setTitle();

private:
    std::vector<Page> pages;
    std::string title;
    Index bookIndex;

};


#endif // BOOK_H_INCLUDED
