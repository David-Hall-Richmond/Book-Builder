//Definition of Book class

#include "Book.h";
#include <iostream>
#include <cstring>

/*
Book Constructor. Creates empty book and sets title only
*/
Book::Book(std::string newTitle)
{
    title=newTitle;

    //std::cerr<<"Book Initializer Ran"<<std::endl;
}

Page Book::getPage(int index)
{
    return pages[index];
}
void Book::addPage(std::string mainText)
{
    Page newPage(title,mainText);
    pages.push_back(newPage);
}

//Used for writing final HTML's to files. Uses the Page method to output to file
void Book::print()
{
    for(int i=0;i<pages.size();i++)
    {
       pages[i].writeToFile();
    }
}

void Book::createPageHTMLS()
{
    for(int i=0;i<pages.size();i++)
    {
       pages[i].buildHTML();
    }
}

int Book::getNumPages()
{
    return pages.size();
}

/*
Finds the title of the book assuming a standard format for books in the Gutenberg project
in which the title follows "Title:" and ends at the start of "Author:" which directly follows
*/
void Book::setTitle()
{
    if(pages.size()==0)title="";
    else
    {
        std::string temp=pages[0].getText();
        int titleIndex=temp.find("Title:")+6;     //length of title, I want to start at the end
        int authorIndex=temp.find("Author:");
        title=temp.substr(titleIndex,(authorIndex-titleIndex));

        //std::cerr<<title<<std::endl;

        for(int i=0;i<pages.size();i++)pages[i].setTitle(title); //all pages are read at once, so title must be set after the fact
    }
}

/*
Builds a master index by looping through all pages and finding/counting all terms
that match the criteria and are not on the stoplist.txt. Once built, removes any
terms that are over the limit and then builds the index HTML file'
*/

void Book::createIndex()
{
    std::string text;
    int pageNumber;

    //std::cerr<<getNumPages()<<std::endl;

    for(int i=0;i<getNumPages();i++)
    {
        text=pages[i].getText();
        pageNumber=i+1;

        //std::cerr<<pageNumber<<" "<<text<<std::endl;
        bookIndex.findTerms(text,pageNumber);
    }

    bookIndex.removeOverThreshold();
    bookIndex.createIndexHTML(title);
}

