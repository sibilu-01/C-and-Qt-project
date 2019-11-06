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
        QJsonObject jsonStats;
        QJsonObject jsonLabelIdentifiers;
        QJsonObject jsonVariableIdentifiers;
        Program();
        Program(string fn): filename(fn) {}
        static string* splitString(string, size_t&);
        static string* splitString(string);
        void compile();
        void execute();
        void print();
};

#endif
