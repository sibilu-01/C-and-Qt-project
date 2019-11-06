#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include "Program/Operand.h"
#include <QJsonObject>
#include <iostream>
#include <sstream>
#include "Program/Program.h"
using namespace std;
class Program;

class Statement {
    public:
        Statement() {}
        virtual ~Statement() {}
        virtual void run() {}
        virtual QJsonObject compile(Program *program, string instr) { return QJsonObject(); }
};

class ReadStmt: public Statement {
    public:
        void run() override;
        QJsonObject compile(Program *program, string instr) override;
};

class DeclIntStmt: public Statement {
    private:
        Operand varName;
    public:
        DeclIntStmt();
        DeclIntStmt(Operand in);
        void run() override;
        QJsonObject compile(Program *program, string instr) override;
};

class EndStmt: public Statement {
    public:
        EndStmt();
        void run() override;
        QJsonObject compile(Program *program, string instr) override;
};

#endif
