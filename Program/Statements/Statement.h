#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include "Program/Operand.h"
#include "Program/Identifier.h"
#include <QJsonObject>
#include <iostream>
#include <sstream>
#include "Program/Program.h"
#include <vector>
using namespace std;
class Program;

class Statement {
    public:
        virtual ~Statement() {}
        virtual void run() = 0;
        virtual QJsonObject compile(Program *program, vector<string> args) = 0;
        Statement() {}
};

class ReadStmt: public Statement {
    private:
        Operand variable;
    public:
        ReadStmt(string varName);
        void run() override;
        QJsonObject compile(Program *program, vector<string> args) override;
};

class DeclIntStmt: public Statement {
    private:
        Operand variable;
    public:
        DeclIntStmt(string varName);
        void run() override;
        QJsonObject compile(Program *program, vector<string> args) override;
};

class EndStmt: public Statement {
    public:
        EndStmt();
        void run() override;
        QJsonObject compile(Program *program, vector<string> args) override;
};

class PrtStmt: public Statement {
    private:
        string variable;
    public:
        PrtStmt(string toprint);
        void run() override;
        QJsonObject compile(Program *program, vector<string> args) override;
};

#endif
