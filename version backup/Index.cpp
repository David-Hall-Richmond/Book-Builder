#include "Index.h"
#include "IndexItem.h"
#include <iostream>
#include <fstream>
#include <sstream>

Index::Index()
{
        std::ifstream stopTextIn("stoplist.txt");
        std::stringstream total;
        total<<stopTextIn.rdbuf();
        stopText=total.str();
        //for(int i=0;i<LETTERS_IN_ALPHABET;i++)
        //    sections[i].initialize();
        //std::cerr<<"Index constructor ran"<<std::endl;

}
void Index::findTerms(std::string toBeIndexed,int pageNum)
{
    std::stringstream textStream(toBeIndexed);
    std::string current;
    //std::cerr<<"got to here"<<std::endl;
    while(textStream>>current || !textStream.eof())
    {
        if(textStream.fail())
        {
            textStream.clear();
            std::string garbage;
            textStream >> garbage;
            continue;
        }
        if(checkTerm(current))
        {
            sections[current[0]].insertTerm(current,pageNum);
        }
    }
}
void Index::createIndexHTML(std::string bookTitle){}

bool Index::checkTerm(std::string word)
{
    return (isalpha(word[0]) && word.length() > 3 && stopText.find(word)==-1);
}
void Index::removeOverThreshold(std::string word)
{
    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
            sections[i].removeOverThreshold();
    }
    print();
}

void Index::print()
{
    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
            sections[i].print();
    }
}
