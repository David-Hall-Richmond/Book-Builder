#include "indexItem.h"


IndexTerms::IndexTerms()=default;
{
    head=nullptr;
}

void IndexTerms::initialize()
{
    head=nullptr;
}

void IndexTerms::insertTerm(std::string newTerm,int pageNum)
{
    indexTerm toAdd;
    toAdd.term=newTerm;
    toAdd.pageNumbers.push_back(pageNum);
    ItemNode* iter;
    if(head==nullptr)
        head=new ItemNode(toAdd,nullptr);
     else
     {
         iter=head;
         std::cerr<<iter->itemInfo.term<<std::endl;
         while(iter->next != nullptr &&
                (iter->next->itemInfo.term > toAdd.term))
                {
                    std::cerr<<iter->itemInfo.term<<std::endl;
                    iter = iter->next;

                }

         indexTerm temp=iter->itemInfo;

         if(temp.term == toAdd.term &&(!temp.pageNumbers[temp.pageNumbers.size()-1]==pageNum))
         {
             addNumber(iter,pageNum);
         }
         else
         {
                ItemNode *newNode = new ItemNode(toAdd,iter->next);
                iter->next = newNode;
         }

      }
}
void IndexTerms::addNumber(ItemNode *toChange,int num)
{
    toChange->itemInfo.pageNumbers.push_back(num);
}

std::string IndexTerms:: convert2HTML(){}

std::string IndexTerms::print()
{
    ItemNode* iter=head;
    std::stringstream ret;
    while(iter!=nullptr)
    {
        ret<<iter->itemInfo.term;
        std::vector<int> listOfNums= iter->itemInfo.pageNumbers;
        for(int i=0;i<listOfNums.size();i++)ret<<listOfNums[i];
    }


    return ret.str();

}

void IndexTerms::removeOverThreshold()
{
    ItemNode* iter=head;
    indexTerm itemInfo;
    while(iter!=nullptr && iter->next!=nullptr)
    {
                itemInfo=iter->itemInfo;
                if(itemInfo.pageNumbers.size()>PAGE_THRESHOLD)
                {
                    ItemNode* temp=iter->next;
                    iter->next = temp->next;
                    delete temp;
                }
    }
}

