#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <QJsonObject>
#include <QJsonDocument>
#include "Program/Statements/Statement.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>
#include <iterator>
#include <map>
using namespace std;

class Statement;
class Program {
    private:
        map<string, Identifier*> identifier;
        map<int, Statement*> statements;
        string filename;
        int comparisonFlag;
    public:
        int error_code = 0;
        Program();
        Program(string fn): filename(fn) {}
        vector<string> splitString(string str);
        void compile();
        void execute();
        void print();

        Identifier* getIdentifier(string name);
        bool identifierExists(string name);
        void addIdentifier(Identifier* ident);

        Statement* getStatement(int index);
        void addStatement(int index, Statement* stat);
};

#endif
