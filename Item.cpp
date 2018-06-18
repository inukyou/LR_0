//
// Created by zhouge on 18-6-6.
//

#include "Item.h"
using namespace std;


bool Item::operator ==(const Item &item) const
{
    if(this->left!=item.left)
        return false;
    if(this->flag!=item.flag)
        return false;
    if(this->rigth!=item.rigth)
        return false;
    return true;
}

bool Item::equal(const Item &item)
{
    return (*this)==item;
}


string Item::toString() const
{
    string s=std::to_string(number)+":  ";
    s+=this->left+"->";
    size_t i;
    for(i=0;i<this->flag;i++)
        s+=this->rigth[i];
    s+=".";
    for(;i<this->rigth.size();i++)
        s+=this->rigth[i];
    return s;
}