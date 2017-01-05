#ifndef INDEXITEM_H_INCLUDED
#define INDEXITEM_H_INCLUDED

#include "indexConstants.h"
#include <string>
#include <sstream>
#include <iostream>


class IndexTerm
{

public:
    void setValues(std::string word,int page);
    void addNumber(int num);
    std::string getTerm();
    bool getFlag();
    std::string tagMaker();

    /*used for debugging
    void print();
    */
private:
    std::string term;
    int pageNumbers[50];
    int numberCount;
    bool flagToRemove=false;
};



#endif // INDEXITEM_H_INCLUDED
