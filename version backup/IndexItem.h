#ifndef INDEXITEM_H_INCLUDED
#define INDEXITEM_H_INCLUDED

#include "indexConstants.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


class IndexTerms
{
protected:
    struct indexTerm
    {
            std::string term;
            std::vector<int> pageNumbers;
    };

    struct ItemNode
    {
        indexTerm itemInfo;
        ItemNode *next=nullptr;

        ItemNode(){};
        ItemNode(indexTerm& newItem,ItemNode *nextNode=nullptr)
        : itemInfo(newItem),next(nextNode)
        {};
    }node;
public:
    IndexTerms();
    void initialize();
    void insertTerm(std::string word,int pageNum);
    void addNumber(ItemNode* toChange,int num);
    void removeOverThreshold();
    bool checkOverLimit();
    std::string convert2HTML();
    std::string getTerm();
    std::string print();
    IndexTerms * start();
    IndexTerms* next();



private:
    void removeNext();
    ItemNode *head=0;

};



#endif // INDEXITEM_H_INCLUDED
