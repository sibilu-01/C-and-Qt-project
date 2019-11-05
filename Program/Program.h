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
using namespace std;

class Program {
    private:
        string filename;
        int comparisonFlag;
    public:
        string* splitString(string, size_t&);
        void compile(string filename);
        void execute();
        void print();
};

#endif
