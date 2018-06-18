//
// Created by zhouge on 18-6-5.
//

#ifndef LR_0_DFA_H
#define LR_0_DFA_H

#include <vector>
#include <string>
#include "Grammar.h"
#include "Status.h"
#include "Item.h"

struct analysisFlag{

    bool error=true;
    std::string s="";
    int number=-1;

    std::string display()const {
        if(error)
            return "    ";
        else if(s=="r")
            return s+std::to_string(number)+"  ";
        else if(s=="acc")
            return "acc ";
        else if(s=="s")
            return s+std::to_string(number)+"  ";
    }
};







class DFA {

public:
    DFA(const Grammar &grammar);
    void showDFA();

    std::set<char> getVT() const;
    std::set<char> getVN() const;

    analysisFlag ACTION(int k,char c) const;
    analysisFlag GOTO(int k,char c) const;
    unsigned int getStatusCount() const;
    std::vector<Item> getItemSet() const;

protected:
    std::vector<Status> statusVector;
    std::vector<Item> itemSet;
    std::string startFlag="";
    void structureDFA();
    void structureDFA(const std::vector<int> &statusNumberList);
    Status Go(const Status &status, char c);
    bool hasStatus(const Status &status);
    std::vector<Item> Closuer(const std::vector<Item> &itemJ);
    Item startItem;
    std::set<char> VT;
    std::set<char> VN;
};

#endif //LR_0_DFA_H
