#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED
#include <string>
#include <iostream>


static int pageCount=0;

//Manages the information for the individual pages of the book
//along with capability to write each HTML file
class Page
{

public:
    Page(std::string title,std::string text);
    std::string getTitle();
    std::string getText();
    void setTitle(std::string newTitle);
    void writeToFile();
    void buildHTML();
    int getPageNumber();


private:
    std::string title;
    std::string mainText;
    std::string htmlText;
    int pageNumber;
    std::string fileName;
    std::string buildPageRefs();
};





#endif // PAGE_H_INCLUDED
