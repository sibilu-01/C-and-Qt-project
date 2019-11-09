#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include "Program/Operand.h"
#include "Program/Identifier.h"
#include <QJsonObject>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class Statement {
    public:
        virtual ~Statement() {}
        virtual void run() = 0;
        virtual QJsonObject compile(map<string, Identifier*> *identifiers, vector<string> args) = 0;
        Statement() {}
};

class ReadStmt: public Statement {
    private:
        Operand variable;
    public:
        ReadStmt(string varName);
        void run() override;
        QJsonObject compile(map<string, Identifier*> *identifiers, vector<string> args) override;
};

class DeclIntStmt: public Statement {
    private:
        Operand variable;
    public:
        DeclIntStmt(string varName);
        void run() override;
        QJsonObject compile(map<string, Identifier*> *identifiers, vector<string> args) override;
};

class EndStmt: public Statement {
    public:
        EndStmt();
        void run() override;
        QJsonObject compile(map<string, Identifier*> *identifiers, vector<string> args) override;
};

class PrtStmt: public Statement {
    private:
        string variable;
    public:
        PrtStmt(string toprint);
        void run() override;
        QJsonObject compile(map<string, Identifier*> *identifiers, vector<string> args) override;
};

#endif
