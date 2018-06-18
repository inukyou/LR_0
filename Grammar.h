//
// Created by zhouge on 18-6-1.
//

#ifndef LR_0_GRAMMAR_H
#define LR_0_GRAMMAR_H

#include <vector>
#include <set>
#include <string>




struct rules{
    std::vector<char> searchflag;
    std::string  left;
    std::string rigth;
};


class Grammar {

public:
    ~Grammar();
     unsigned long getCount();
     void addRules(const std::string &left,const std::string &rigth);
     std::vector<rules> getRulesSet()const;
     void setStartFlag(const std::string &startFlag);
     std::string getStratFlag() const;

    std::set<char> getVT() const;
    std::set<char> getVN() const;


protected:
    std::set<char> VT;
    std::set<char> VN;
    std::vector<rules> rulesSet;
    std::string startFlag="";
};


#endif //LR_0_GRAMMAR_H
