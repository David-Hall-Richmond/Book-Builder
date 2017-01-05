/*

-create the rest of the implementation for creating the pages then move on to index
-still need to define createBook and getTitle methods
*/


#include <iostream>
#include <fstream>
#include "Book.h"
#include "indexConstants.h"

using namespace std;

string readInPage(istream& in);
void createBook(istream& in,Book& toMake);
string getTitle(istream& in);

/*HTML Book Maker: Converts a raw text file into individual HTML pages*/
int main(int argc, char** argv)
{
    if(argc<1)
    {
        cerr<<"Use format 'bookMaker [input file name]"<<endl;
    }
    else
    {
        ifstream in(argv[1]);
        //string title=getTitle(in);didn't end up using, noted in discussion so I left the comment in

        Book myBook("");

        createBook(in,myBook);

        myBook.setTitle();

        myBook.createPageHTMLS();

        myBook.createIndex();

        myBook.print();
    }

    return 0;
}

/*reads in string from file line by line up to limiting constant
returns one string with main page text'
*/
string readInPage(istream& in)
{
    int lineCount=0;
    string newPage="";
    string inString;
    while(lineCount<MAX_LINES_PER_PAGE && getline(in,inString))
    {
        newPage+=inString+"\n";
        lineCount++;
    }


    //cerr<<newPage<<endl;
    return newPage;
}

/*
reads in MAX_LINES_PER_PAGE length pages from input using readInPage method and directly
adds to the master 'book'
*/
void createBook(istream& in,Book& toMake)
{
    while(in)
    {
        toMake.addPage(readInPage(in));
        //toMake.createIndex();
    }
}

