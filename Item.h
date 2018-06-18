//
// Created by zhouge on 18-6-6.
//

#ifndef LR_0_ITEM_H
#define LR_0_ITEM_H

#include <string>

class Item {

public:
    std::string left;
    std::string rigth;
    unsigned long flag;
    int number=-1;
    std::string toString()const;

    bool operator ==(const Item &item) const;
    bool equal(const Item &item);

};


#endif //LR_0_ITEM_H
