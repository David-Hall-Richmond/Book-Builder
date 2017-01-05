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
    void removeOverThreshold();

private:
    //processing and term entry methods
    void processWord(std::string newTerm,int pageNum,int letterSection);
    int  findItem(int letterSection,std::string word,int termCount);
    bool checkTerm(std::string word);
    std::string cleanWord (std::string word);
    void addNewTerm(int letterSection,IndexTerm& toAdd,int index);
    void overWrite(int letterSection,int indexToOverwrite);
    //html creation methods
    std::string sectionTagBuilder();
    void indexTermBuilder(std::ofstream& out);

    /*used to debug
    Debugging-void printWordCounts();
    void printSection();
    void print();
    */
    char letters[LETTERS_IN_ALPHABET];

    IndexTerm sections[LETTERS_IN_ALPHABET][200];
    int wordsInSection[LETTERS_IN_ALPHABET];//count of the number of valid IndexTerms in the each section
    std::string sectionHeadings[26]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    std::string stopText;
};



#endif // INDEX_H_INCLUDED
