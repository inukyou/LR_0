//
// Created by zhouge on 18-6-1.
//

#include "AnalysisTable.h"
#include <iostream>
#include <list>

using namespace std;


void printLine(int count,list<int>statusStack,list<char> charStack,list<char> inPutStack,analysisFlag actionFlag);


AnalysisTable::AnalysisTable(DFA dfa){
    itemSet=dfa.getItemSet();
    vector<analysisFlag> v(dfa.getStatusCount());

    for(char c:dfa.getVT())
    {
        for(size_t i=0;i<dfa.getStatusCount();i++)
            v[i]=dfa.ACTION(i,c);
        actionTable.insert(pair<char,vector<analysisFlag>>(c,v));
    }
    for(size_t i=0;i<dfa.getStatusCount();i++)
        v[i]=dfa.ACTION(i,'#');
    actionTable.insert(pair<char,vector<analysisFlag>>('#',v));

    vector<analysisFlag> v2(dfa.getStatusCount());
    for(char c:dfa.getVN())
    {
        for(size_t i=0;i<dfa.getStatusCount();i++)
            v2[i]=dfa.GOTO(i,c);
        gotoTable.insert(pair<char,vector<analysisFlag>>(c,v2));
    }


}


void AnalysisTable::display() const
{
    vector<char> VT;
    cout<<"    ";
    for(auto it=actionTable.begin();it!=actionTable.end();it++)
    {
        cout<<(*it).first<<"     ";
        VT.push_back((*it).first);
    }
    cout<<" |   ";
    vector<char> VN;
    for(auto it=gotoTable.begin();it!=gotoTable.end();it++)
    {
        cout<<(*it).first<<"     ";
        VN.push_back((*it).first);
    }

    cout<<endl;
    size_t rowCount=(*actionTable.begin()).second.size();

    for(size_t i=0;i<rowCount;i++)
    {
        cout<<i<<"  ";
        for(char vt:VT)
        {
            cout<<actionTable.at(vt).at(i).display()<<"  ";
        }
        cout<<"  |   ";

        for(char vn:VN)
        {
            cout<<gotoTable.at(vn).at(i).display()<<"  ";
        }
        cout<<endl;
    }
}

analysisFlag AnalysisTable::queryACTION(char inputChar,int statusNumber)
{
    return actionTable.at(inputChar).at(statusNumber);
}
analysisFlag AnalysisTable::queryGOTO(char gotoChar,int statusNumber)
{
    return gotoTable.at(gotoChar).at(statusNumber);
}



bool AnalysisTable::AnalysisString(const string &s)
{
    cout<<"\n\n\n";

    list<int> statusStack;
    statusStack.push_back(0);
    list<char> charStack;
    charStack.push_back('#');
    list<char> inPutStack;

    for(auto it=s.begin();it!=s.end();it++)
        inPutStack.push_back(*it);
    inPutStack.push_back('#');

    int count=1;
    int statusNumber;
    cout<<"步骤             状态栈                       符号栈                   输入串                    ACTION               GOTO"<<endl;
    while(true)
    {
        char inputChar=inPutStack.front();
        statusNumber=statusStack.back();
        analysisFlag actionFlag=queryACTION(inputChar,statusNumber);
        analysisFlag gotoFlag;

/******************打印分析过程**************/

        printLine(count++,statusStack,charStack,inPutStack,actionFlag);

/******************打印分析过程**************/

        if(actionFlag.s=="r")
        {
            int itemNumber=actionFlag.number;
            char gotoChar=itemSet.at(itemNumber).left[0];
            for(size_t i=0;i<itemSet.at(itemNumber).rigth.size();i++) {
                statusStack.pop_back();
                charStack.pop_back();
            }
            statusNumber=statusStack.back();
            gotoFlag=queryGOTO(gotoChar,statusNumber);

            statusStack.push_back(gotoFlag.number);
            charStack.push_back(itemSet.at(itemNumber).left[0]);

            cout<<"                 ";
            cout<<gotoFlag.display();
        }
        else if(actionFlag.s=="s") {
            inPutStack.pop_front();
            charStack.push_back(inputChar);
            statusStack.push_back(actionFlag.number);
        }
        else if(actionFlag.s=="acc")
            break;

        cout<<endl;
    }
    return true;
}

void printLine(int count,list<int>statusStack,list<char> charStack,list<char> inPutStack,analysisFlag actionFlag)
{
    int spaceCount=27;
    cout<<" "<<count++<<"               ";
    for(auto v:statusStack) {
        if (v >= 10) {
            cout << "(" << v << ")";
            spaceCount-=4;
        }
        else {
            cout << v;
            spaceCount--;
        }
    }
    for(int i=0;i<=spaceCount;i++)
        cout<<" ";
    for(auto v:charStack)
        cout<<v;
    spaceCount=23-charStack.size();
    for(int i=0;i<=spaceCount;i++)
        cout<<" ";
    for(auto v:inPutStack)
        cout<<v;
    spaceCount=24-inPutStack.size();
    for(int i=0;i<=spaceCount;i++)
        cout<<" ";
    cout<<actionFlag.display();
}

