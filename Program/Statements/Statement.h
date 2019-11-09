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
        virtual QJsonObject compile(vector<string> args) = 0;
        Statement() {}
};

class ReadStmt: public Statement {
    private:
        Operand variable;
    public:
        ReadStmt(Identifier* var);
        void run() override;
        QJsonObject compile(vector<string> args) override;
};

class DeclIntStmt: public Statement {
    private:
        Operand variable;
    public:
        DeclIntStmt(map<string, Identifier*> *identifiers, string varName);
        void run() override;
        QJsonObject compile(vector<string> args) override;
};

class EndStmt: public Statement {
    public:
        EndStmt();
        void run() override;
        QJsonObject compile(vector<string> args) override;
};

class PrtStmt: public Statement {
    private:
        string variable = "";
        Operand identifier = nullptr;
    public:
        PrtStmt(string toprint);
        PrtStmt(Identifier* ident);
        void run() override;
        QJsonObject compile(vector<string> args) override;
};

class CmpStmt: public Statement {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        CmpStmt(Identifier* variableLeft, Identifier* variableRight);
        void run() override;
        QJsonObject compile(vector<string> args) override;
};

class JMoreStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JMoreStmt(Identifier* jump);
        void run() override;
        QJsonObject compile(vector<string> args) override;
};

class JumpStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JumpStmt(Identifier* jump);
        void run() override;
        QJsonObject compile(vector<string> args) override;
};
#endif
