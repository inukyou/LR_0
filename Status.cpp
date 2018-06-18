//
// Created by zhouge on 18-6-6.
//

#include <iostream>
#include "Status.h"

using namespace std;

bool Status::operator ==(const Status &status)
{
    if(this->items.size()!=status.items.size())
        return false;
    for(auto v:this->items)
    {
        bool find=false;
        for(auto v2:status.items)
            if(v==v2)
                find=true;
        if(!find)
            return false;

    }
    return true;
}


bool Status::addItem(const Item &item)
{
    for(auto v:this->items)
    {
        if(v==item)
            return false;
    }
    for(char c:item.rigth) {
        lettters_Go.insert(c);
    }
    this->items.push_back(item);
    return true;
}



unsigned long Status::getItemCount()
{
    return items.size();
}

string Status::toString()const {
    string s= "status number:"+to_string(statusFlag)+"\n";
    s+="letters:";
    for(char c:lettters_Go) {
        string tmp=" ";
        tmp[0]=c;
        s += tmp + " ";
    }
    s+="\n";
    for(auto item:items)
        s+=item.toString()+"\n";
    return s;
}