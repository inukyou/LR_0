//
// Created by zhouge on 18-6-6.
//

#ifndef LR_0_STATUS_H
#define LR_0_STATUS_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Item.h"
#include "Grammar.h"


#define REDUCED 1
#define  GO_ON 2



class Status {



public:
    int statusFlag=-1;
    int type=0;
    std::vector<Item> items;
    std::map<char, int> link;
    bool operator ==(const Status &status);
    bool addItem(const Item &item);
    unsigned long getItemCount();
    std::set<char> lettters_Go;
    std::string toString()const;

};


#endif //LR_0_STATUS_H
