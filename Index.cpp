#include "Index.h"
#include "IndexItem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//Creates new Index object.
//reads in stoplist from file and initializes all word counts to 0
Index::Index()
{
        std::ifstream stopTextIn("stoplist.txt");
        std::stringstream total;
        total<<stopTextIn.rdbuf();
        stopText=total.str();

        //std::cerr<<"Index Initializer Ran"<<std::endl;

        for(int i=0;i<LETTERS_IN_ALPHABET;i++)wordsInSection[i]=0;
}

/*
Primary function for adding terms to the master index.
Reads in from a string stream word by word until the end of the string.
Checks if the string passes the criteria and sends it to be either added or the page number marked
*/
void Index::findTerms(std::string toBeIndexed,int pageNum)
{
    std::stringstream textStream(toBeIndexed);
    std::string current;

    while(textStream>>current || !textStream.eof())
    {
        if(checkTerm(current))
        {
            current=cleanWord(current);
            int index=(int)(current[0])-(int)'a'; //uses the lowercase first letter to find section

            //std::cerr<<"Processing word "<<current<<" with char "<<current[0]<<" at index "<<index<<std::endl;
            processWord(current,pageNum,index);
        }
    }
    //for debug only
    //printWordCounts();

}

//Checks the given term against the criteria to be placed in the index
bool Index::checkTerm(std::string word)
{
    for(int i=0;i<word.length();i++)
    {
        if(!((word[i]>='a') && (word[i]<='z')) && (!(word[i]>='A' && word[i]<='Z')))
            return false;
    }

    return (word.length() > 3 && stopText.find(word)==-1);
}

/*
Adapted from prior assignment method. Takes out punctuation
and converts to lower case if needed, returning a word appropriate for an index
*/
std::string Index::cleanWord (std::string word)
{
  std::string result;
  for (int i = 0; i < word.size(); ++i)
    {
      char c = word[i];
      if (c == '-')
	result += c;
      else if (c >= 'a' && c <= 'z')
	result += c;
      else if (c >= 'A' && c <= 'Z')
	result += (c - 'A' + 'a'); // converts to lower-case
    }
  return result;
}

/*
Operates only on the specific section of letters. If the term is not present,
it is added to the list and the counts are incremented. Otherwise if the page
is not already marked for the term, the current page number is added to the term
*/
void Index::processWord(std::string newTerm,int pageNum,int letterSection)
{
         newTerm=cleanWord(newTerm);
         IndexTerm toAdd;
         toAdd.setValues(newTerm,pageNum);

         /*if(wordsInSection[letterSection]==0)
         {
            std::cerr<<"Incrementing words in section "<<letterSection<<" to add "<<newTerm<<std::endl;
            sections[letterSection][0]=toAdd;
            wordsInSection[letterSection]++;
         }*/

         int index=findItem(letterSection,newTerm,wordsInSection[letterSection]);

         //if(newTerm[0]=='s')
         //std::cerr<<"Index of newTerm: "<<newTerm<<" "<<index<<std::endl;

         if(wordsInSection[letterSection]!=0 && sections[letterSection][index].getTerm() == newTerm)
         {
             sections[letterSection][index].addNumber(pageNum);
         }
         else
         {
            addNewTerm(letterSection,toAdd,index);
            wordsInSection[letterSection]++;
         }

         //for debug only
         //if(newTerm[0]=='s')
            {
                //std::cerr<<"Added: "<<sections[letterSection][index].getTerm()<<" to section that now has "<<wordsInSection[letterSection]<<" words"<<std::endl;
                //std::cerr<<"Section "<<letterSection<<" contains "<<wordsInSection[letterSection]<< " words "<<std::endl;
                //printSection(letterSection);
            }

}

//returns the index where the item is found or where it should be inserted if not found
int Index::findItem(int letterSection,std::string word,int termCount)
{
    int index=0;
    while(index<termCount && sections[letterSection][index].getTerm()< word )
    {
        index++;
    }

    return index;
}

//adds new IndexTerm to Index at the given index number
void Index::addNewTerm(int letterSection,IndexTerm& toAdd,int index)
{
    int start=wordsInSection[letterSection];
    for(int i=start+1;i>index;i--)
    {
        sections[letterSection][i]=sections[letterSection][i-1];
    }
    sections[letterSection][index]=toAdd;
}

/*
Checks all IndexTerms in the index and uses overwrite method to
delete if they are over the maximum page threshold
*/
void Index::removeOverThreshold()
{
    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
        for(int j=0;j<wordsInSection[i];j++)
        {
            if(sections[i][j].getFlag())overWrite(i,j);
        }
    }
    //for debugging purposes only:
    //printSection();
}

/*
Used to delete terms over the PAGE_THRESHOLD limit.Starts from index
and moves the elements that follow up by one. May leave extra element
copies at end but this is managed with the word count per section
*/
void Index::overWrite(int letterSection,int indexToOverwrite)
{
    for(int i=0;i<wordsInSection[letterSection];i++)
    {

        sections[letterSection][i]=sections[letterSection][i+1];
    }
    wordsInSection[letterSection]--;
}

/*
Creates the master index html file. Uses manual entry of standard HTML tags.
tags for the links at top and individual lettered sections are generated automatically
in separate methods. Outputs to the file buffer several times as I found attempting to
concatenate the entire string would sometimes overtake memory on larger books
*/
void Index::createIndexHTML(std::string bookTitle)
{
    std::ofstream out("indexPage.html");

    std::string htmlString="";
    htmlString+="<html>\n";
    htmlString+=  "<head>\n";
    htmlString+="    <title>";
    htmlString+=bookTitle;
    htmlString+="</title>\n";
    htmlString+="  </head>\n\n";
    htmlString+="  <body>\n";
    htmlString+="    <p>\n";
    htmlString+="  <a href=\"page0001.html\"First</a>";
    htmlString+="    </p>\n";
    htmlString+="    <hr/>\n";
    htmlString+="    <p>\n";

    out<<htmlString;
    htmlString="";
    htmlString+=sectionTagBuilder();
    htmlString+="    <h1>Index</h1>\n\n";

    out<<htmlString;
    htmlString="";
    indexTermBuilder(out);
    htmlString+="  </body>\n";
    htmlString+="</html>";

    out<<htmlString;
    out.close();
}


//Builds the links to the individual sections
std::string Index::sectionTagBuilder()
{
    std::string ret="";
    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
        ret+="      <a href=\"#"+sectionHeadings[i]+"\">"+sectionHeadings[i]+"</a>\n";
    }
    return ret;

    //std::cerr<<ret;
}

//builds the sectioned tags for each term, adding a lettered header at the start
//each new letter's section
void Index::indexTermBuilder(std::ofstream& out)
{
    std::string ret="";

    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
        //std::cerr<<"Words in "+sectionHeadings[i]+": "<<wordsInSection[i]<<std::endl;
        if(wordsInSection[i]>0)
        {
            out<<"    <h2 id=\""+sectionHeadings[i]+"\">"+sectionHeadings[i]+"</h2>\n";
            std::string ret="";
            for(int j=0;j<wordsInSection[i];j++)
            {
                //std::cerr<<"I: "<<i<<" J: "<<j<<"Words in section: "<<wordsInSection[i]<<std::endl;
                ret+=sections[i][j].tagMaker();
                out<<ret;
                //std::cerr<<ret;
                ret="";
            }
        }
    }
    out<<"  </ul>\n\n";
    //std::cerr<<ret;
}

//used for debugging
/*void Index::print()
{
    //std::cerr<<"Printing current Index Terms"<<std::endl;
    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
        for(int j=0;j<wordsInSection[i];j++)
        {
            //std::cerr<<"i: "<<i<<"j: "<<j<<std::endl;
            sections[i][j].print();
        }

    }
}*/

/*used for debugging
void Index::printWordCounts()
{
    for(int i=0;i<26;i++)
    {
        std::cerr<<wordsInSection[i]<<" ";
    }
    std::cerr<<std::endl;
}*/

/*used for debugging
void Index::printSection()
{
    for(int i=0;i<LETTERS_IN_ALPHABET;i++)
    {
        for(int j=0;j<wordsInSection[i];j++)
        {
            //std::cerr<<"I: "<<i<<" J: "<<j<<std::endl;
            sections[i][j].print();
        }

    }
    //std::cerr<<std::endl;
}*/
