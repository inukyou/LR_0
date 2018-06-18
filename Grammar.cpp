//
// Created by zhouge on 18-6-1.
//

#include <malloc.h>
#include "Grammar.h"


using namespace std;

unsigned long Grammar::getCount()
{
    return rulesSet.size();
}

void Grammar::addRules(const string &left,const string &rigth)
{
    rules r;
    r.rigth=rigth;
    r.left=left;
    rulesSet.push_back(r);
    VN.insert(left[0]);
    for(char c:rigth) {
        if (c >= 'a' && c <= 'z')
            VT.insert(c);
        else
            VN.insert(c);
    }

}


void Grammar::setStartFlag(const string &startFlag)
{
    this->startFlag=startFlag;
}

vector<rules> Grammar::getRulesSet()const {
    return rulesSet;
}

string Grammar::getStratFlag() const
{
    return startFlag;
}

Grammar::~Grammar() {

}

set<char> Grammar::getVT() const
{
    return VT;
}
set<char> Grammar::getVN() const
{
    return VN;
}