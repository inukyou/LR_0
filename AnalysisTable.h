//
// Created by zhouge on 18-6-1.
//

#ifndef LR_0_ANALYSISTABLE_H
#define LR_0_ANALYSISTABLE_H

#include <map>
#include "DFA.h"


class AnalysisTable {
public:
    AnalysisTable(DFA dfa);
    void display() const;

    bool AnalysisString(const std::string &s);

    analysisFlag queryACTION(char inputChar,int statusNumber);
    analysisFlag queryGOTO(char gotoChar,int statusNumber);


protected:
    std::map<char,std::vector<analysisFlag>> actionTable;
    std::map<char,std::vector<analysisFlag>> gotoTable;
    std::vector<Item> itemSet;
};


#endif //LR_0_ANALYSISTABLE_H
