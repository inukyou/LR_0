#include <iostream>
#include <string>
#include <fstream>
#include "Grammar.h"
#include "DFA.h"
#include "AnalysisTable.h"

using namespace std;

Grammar textTogrammar(string path);

int main() {

    string path="/home/zhouge/桌面/grammar.txt";

    //Grammar grammar;
    Grammar grammar=textTogrammar(path);


/*
    grammar.addRules("S","E");
    grammar.addRules("E","aA");
    grammar.addRules("E","bB");
    grammar.addRules("A","cA");
    grammar.addRules("A","d");
    grammar.addRules("B","cB");
    grammar.addRules("B","d");*/

    /*grammar.addRules("S","A");
    grammar.addRules("S","B");
    grammar.addRules("A","aAb");
    grammar.addRules("A","c");
    grammar.addRules("B","aBb");
    grammar.addRules("B","d");
    //grammar.addRules("B","d");*/

/*
    grammar.addRules("S","aAcBe");
    grammar.addRules("S","")
    grammar.addRules("A","b");
    grammar.addRules("A","Ab");
    grammar.addRules("B","d");*/

    string startFlag="S";
    cout<<"please input the StartFlag: ";
    cin>>startFlag;
    cout<<endl<<endl;
    grammar.setStartFlag(startFlag);

    DFA dfa(grammar);
    dfa.showDFA();
    AnalysisTable analysisTable(dfa);
    analysisTable.display();

    string input="";
    cout<<endl<<endl;
    cout<<"please input the inputString:";
    cin>>input;
    cout<<endl<<endl;
    analysisTable.AnalysisString(input);
    return 0;

}


Grammar textTogrammar(string path)
{
    ifstream infile;
    infile.open(path.data());
    string sline;
    Grammar grammar;
    while(getline(infile,sline))
    {
        string left="",rigth="";
        if(sline.empty()||sline.size()==0)
            continue;
        for(char c:sline)
        {
            if(c!=' ')
            {
                if(left.empty()&&c!='-'&&c!='>'&&c!='|')
                    left.push_back(c);
                else if(c!='-'&&c!='>'&&c!='|')
                    rigth.push_back(c);
                else if(c=='|') {
                    grammar.addRules(left, rigth);
                    //cout<<left<<"------"<<rigth<<endl;
                    rigth="";
                }
            }
        }
        //cout<<left<<"------"<<rigth<<endl;
        grammar.addRules(left, rigth);
    }
    return grammar;
}