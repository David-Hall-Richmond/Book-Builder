#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED

#include "IndexItem.h"
#include <sstream>
#include <array>

class Index{

    static const int LETTERS_IN_ALPHABET=26;

public:
    Index();
    void findTerms(std::string toBeIndexed,int pageNum);
    void createIndexHTML(std::string bookTitle);

private:
    bool checkTerm(std::string word);
    void removeOverThreshold(std::string word);
    void print();

    enum LETTERS{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
    char letters[LETTERS_IN_ALPHABET];

    IndexTerms sections[LETTERS_IN_ALPHABET];
    std::string stopText;
};



#endif // INDEX_H_INCLUDED
