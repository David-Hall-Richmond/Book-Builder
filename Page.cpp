//definition of page object
#include "Page.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

/*
Constructor sets member variables and uses page number to create
the filename for this page to ouput HTML
*/
Page::Page(std::string bookTitle,std::string text)
{
    title=bookTitle;
    mainText=text;
    pageNumber=++pageCount;
    std::stringstream fileMaker;
    fileName="page";
    fileMaker<<std::setw(4)<<std::setfill('0')<<pageNumber;
    fileName+=fileMaker.str()+".html";
    htmlText="";
    //std::cerr<<title<<std::endl;

}
std::string Page::getTitle()
{
    return title;
}
std::string Page::getText()
{
    return mainText;
}

int Page::getPageNumber()
{
    return pageNumber;
}

void Page::setTitle(std::string newTitle)
{
    title=newTitle;
}

//Only handles file output, the bulk of the work is done in the buildHTML function
void Page::writeToFile()
{
    std::ofstream out(fileName);
    out<<htmlText;
    out.close();
}

//Builds one string to turn page into HTML code.
void Page::buildHTML()
{

    htmlText="<html>\n";
    htmlText+="  <head>\n";
    htmlText+="    <title>"+title+"</title>\n";
    //std::cerr<<title<<std::endl;
    htmlText+="  </head>\n";
    htmlText+="  <body>\n";
    //std::cerr<<"code gets to buildHTML just before buildPageRefs()"<<std::endl;
    htmlText+=buildPageRefs();
    //std::cerr<<"Code gets past buildPageRefs"<<std::endl;
    htmlText+="    <hr/>\n";
    htmlText+="    <pre>\n";
    htmlText+=mainText;
    htmlText+="    </pre>\n";
    htmlText+="  </body>\n";
    htmlText+="</html>\n";
}

//creates the links, in HTML code,if needed, for the next, previous, and index pages
std::string Page::buildPageRefs()
{
    std:: string retString = "    <p>\n";
    std::stringstream pNumbers;
    std::string previous;
    std::string next;
    std::string index;
    pNumbers<<std::setw(4)<<std::setfill('0');

    if(pageNumber>1)
    {
        pNumbers<<pageNumber-1;
        previous=pNumbers.str();
        retString+="      <a href=page\""+previous+".html\">Prev</a>,";
    }

    pNumbers<<std::flush;
    if(pageNumber<pageCount)
    {
        pNumbers<<pageNumber+1;
        next=pNumbers.str();
        retString+="      <a href=page\""+next+".html\">Next</a>,";
    }

    pNumbers<<std::flush;
    pNumbers<<pageCount+1;
    index=pNumbers.str();
    retString+="      <a href=\"indexPage.html\">Index</a>\n    </p>\n";

    return retString;

}
