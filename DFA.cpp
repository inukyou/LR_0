//
// Created by zhouge on 18-6-5.
//

#include "DFA.h"
#include <iostream>

using namespace std;



bool hasItem(vector<Item> &items, const Item &item);


DFA::DFA(const Grammar &grammar)
{
    VT=grammar.getVT();
    VN=grammar.getVN();

    vector<rules> RulesSet=grammar.getRulesSet();
   this->startFlag=grammar.getStratFlag();
   unsigned int Scount=0;
   bool SFlag=false;
    for(auto v:RulesSet)
    {
        if(!SFlag)
            for(char c:v.rigth) {
                if (this->startFlag == (c + "")) {
                    SFlag=true;
                    Item item_S;
                    item_S.left = "S'";
                    item_S.rigth = startFlag;
                    item_S.flag = 0;
                    startFlag = "S'";
                    item_S.number=itemSet.size();
                    itemSet.push_back(item_S);
                    startItem=item_S;
                    break;
                }
            }
        if(!SFlag&&v.left==startFlag&&Scount>0)
        {
            Scount++;
            SFlag=true;
            Item item_S;
            item_S.left = "S'";
            item_S.rigth = startFlag;
            item_S.flag = 0;
            startFlag = "S'";
            item_S.number=itemSet.size();
            itemSet.push_back(item_S);
            startItem=item_S;
        }else if(v.left==startFlag)
            Scount++;

        Item item;
        item.left=v.left;
        item.rigth=v.rigth;
        item.flag=0;
        item.number=itemSet.size();
        itemSet.push_back(item);
        if(!SFlag&&grammar.getStratFlag()==v.left)
            startItem=item;
    }

    structureDFA();

}





vector<Item> DFA::Closuer(const vector<Item> &itemJ)
{
    vector<Item> newItems(itemJ);
    int count;
    int r=0;
    do{
        count=newItems.size();
        for(int i=r++;i<newItems.size();i++)
        {
            for(Item v2:itemSet)
            {
                unsigned long index1=newItems[i].flag;
                if(index1<newItems[i].rigth.size()) {
                    string newStartFlag=" ";
                    newStartFlag[0]=newItems[i].rigth[index1];
                    if (newStartFlag == v2.left && !hasItem(newItems, v2)) {
                        newItems.push_back(v2);

                    }
                }
            }
        }
    }while(count<newItems.size());
    return newItems;
}



Status DFA::Go(const Status &status,char c)
{

    Status status_new;
    for(Item item:status.items) {
        if (item.flag < item.rigth.size() && item.rigth[item.flag] == c) {
            Item newItem = item;
            newItem.flag++;
            newItem.number=item.number;
            status_new.addItem(newItem);
        }
    }

    if(status_new.items.size()>0) {
        //cout<<status.statusFlag<<"-"<<c<<endl;
        status_new.statusFlag = statusVector.size();
        vector<Item> ClosureItems = Closuer(status_new.items);
        for (Item item:ClosureItems)
            status_new.addItem(item);
        //cout << status_new.toString();
    }
    return  status_new;
}



void DFA::structureDFA()
{
    Status status0;
    status0.statusFlag=0;
    vector<Item> itemS;
    itemS.push_back(startItem);
    for(Item closureItem:Closuer(itemS)) {
        status0.addItem(closureItem);
    }

    statusVector.push_back(status0);

    vector<int> statusNumberList;
    for(char c:status0.lettters_Go)
    {
        Status status_new=Go(status0,c);


        if(status_new.statusFlag==-1)
            continue;
        int i=0;
        bool hasThisStatus=false;
        for(i=0;i<statusVector.size();i++)
        {
            if(statusVector[i]==status_new)
            {
                hasThisStatus=true;
                break;
            }
        }

        status_new.statusFlag=i;
        statusVector[0].link.insert(std::pair<char,int>(c,i));
        //cout<<c<<"-"<<status0.link.at(c)<<endl;
        if(!hasThisStatus) {
            statusVector.push_back(status_new);
            statusNumberList.push_back(i);
        }
    }
    if(statusNumberList.size()>0)
        structureDFA(statusNumberList);
}

void DFA::structureDFA(const vector<int> &statusNumberList)
{

    for(auto statusnumber:statusNumberList)
    {
        vector<int> statusNumberList;
        Status status=statusVector[statusnumber];
        for(char c:status.lettters_Go)
        {
            Status status_new=Go(status,c);

            if(status_new.statusFlag==-1)
                continue;
            int i=0;
            bool hasThisStatus=false;
            for(i=0;i<statusVector.size();i++)
            {
                if(statusVector[i]==status_new)
                {
                    hasThisStatus=true;
                    break;
                }
            }

            status_new.statusFlag=i;
            statusVector[statusnumber].link.insert(std::pair<char,int>(c,i));
            //cout<<c<<"-"<<status.link.at(c)<<"!!!"<<i<<endl;
            if(!hasThisStatus) {
                statusVector.push_back(status_new);
                statusNumberList.push_back(i);
            }
        }
        if(statusNumberList.size()>0)
            structureDFA(statusNumberList);
    }
}


void DFA::showDFA(){
    cout<<"statusCount:"<<this->statusVector.size()<<endl;

    for(Item item1:itemSet)
        cout<<item1.toString()<<endl;
    cout<<"startItem:"<<this->startItem.toString()<<endl;
    cout<<"startFlag:"<<this->startFlag<<endl;


    cout<<endl;
    cout<<endl;
    cout<<endl;
    for(auto status:statusVector)
    {
        cout<<"I"<<status.statusFlag<<endl;
        for(auto item:status.items)
            cout<<item.toString()<<endl;
        cout<<"linK:";
        for(map<char,int>::iterator it=status.link.begin();it!=status.link.end();it++)
        {
            cout<<(*it).first<<"-"<<(*it).second<<"   ";
        }
        cout<<endl;
        cout<<endl;
    }


}


set<char> DFA::getVT() const
{
    return VT;
}
set<char> DFA::getVN() const
{
    return VN;
}


bool DFA::hasStatus(const Status &status)
{
    for(auto v:statusVector)
    {
        if(v==status)
            return true;
    }
    return false;
}

bool hasItem(vector<Item> &items, const Item &item)
{

    for(Item v:items)
        if(v==item) {
            return true;
        }

    return false;

}

analysisFlag DFA::ACTION(int k,char c) const
{
    Status status=statusVector[k];
    analysisFlag flag;
    if(status.items[0].rigth.size()>status.items[0].flag)//移进
    {
        flag.s = "s";
        try {
            flag.number = statusVector[k].link.at(c);
            flag.error=false;
        }catch (exception e)
        {
            flag.error=true;
        }
    }
    else if(status.items[0].rigth.size()==status.items[0].flag&&status.items[0].left!=startFlag)
    {
        flag.s = "r";
        flag.error=false;
        flag.number=status.items[0].number;
    }

    if(c=='#')
        for(Item item:status.items)
        {
            if(item.left==startFlag&&item.flag==item.rigth.size()) {
                flag.error=false;
                flag.s = "acc";
                return flag;
             }
        }


    return flag;
}
analysisFlag DFA::GOTO(int k,char c) const
{
    Status status=statusVector[k];
    analysisFlag flag;
    try {
        flag.error=false;
        flag.s="r";
        flag.number=status.link.at(c);
    }catch (exception e) {
        flag.error=true;
    }
    return flag;
}

unsigned int DFA::getStatusCount() const
{
    return statusVector.size();
}

std::vector<Item> DFA::getItemSet() const
{
    return itemSet;
}