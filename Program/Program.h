#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <QJsonObject>
#include <QJsonDocument>



// Identifiers
#include "Program/Identifier.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>
#include <iterator>
#include <map>

class Statement;
class Program {
    private:
        std::map<std::string, Identifier*> identifier;
        std::map<int, Statement*> statements;
        std::string filename;
        int comparisonFlag;
    public:
        int error_code = 0;
        Program();
        Program(std::string);
        ~Program();
        std::vector<std::string> splitString(std::string);
        std::string compile();
        void execute();
        void print();

        Identifier* getIdentifier(std::string);
        bool identifierExists(std::string);
        void addIdentifier(Identifier*);

        Statement* getStatement(int);
        void addStatement(int, Statement*);
};

#endif
