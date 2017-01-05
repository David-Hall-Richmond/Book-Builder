#include "indexItem.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

//sets the values of a new IndexTerm. Once created, use addNumber to add more numbers to the term
void IndexTerm::setValues(std::string word,int page)
{
    term=word;
    pageNumbers[0]=page;
    numberCount=1;
}

/*
//if the number is not present, adds to the end of the page number array
//if it is a new number and it puts it over the limit, doesn't add and just
//flags for removal
*/
void IndexTerm::addNumber(int num)
{
    if(numberCount<=PAGE_THRESHOLD && pageNumbers[numberCount-1]!=num)
    {
        pageNumbers[numberCount]=num;
        numberCount++;
    }
    else if(numberCount>PAGE_THRESHOLD) flagToRemove=true;
}


//creates tag for this IndexItem including term and all page #'s
std::string IndexTerm::tagMaker()
{

    std::string ret="";
    std::string formatted;
    std::string format;
    ret+="    <li>"+term+"\n";
    for(int i=0;i<numberCount;i++)
    {
        std::stringstream ss;
        std::stringstream tt;
        ss<<std::setw(4)<<std::setfill('0');
        ss<<pageNumbers[i];
        tt<<i+1;
        formatted=ss.str();
        format=tt.str();
        ss.clear();
        tt.clear();
        ret+="      <a href=\"page"+formatted+".html\">"+format+"</a>\n";

    }
    ret+="    </li>\n";
    //std::cerr<<ret<<std::endl<<"BREAK"<<std::endl;
    return ret;
}

std::string IndexTerm::getTerm()
{
    return term;
}

bool IndexTerm::getFlag()
{
    return flagToRemove;
}

/* used for debugging
void IndexTerm::print()
{
    //std::cerr<<"Printing item"<<std::endl;

    std::string itemString="";
    itemString+=term+" ";

    for(int i=0;i<numberCount;i++)
    {
        std::stringstream in;
        in<<std::setw(4)<<std::setfill('0');
        in<<pageNumbers[i];
        itemString+=in.str()+" ";
        in.clear();
    }
    std::cout<<"Number of pages: "<<numberCount<<std::endl;
    std::cout<<itemString<<std::endl;
}
*/

