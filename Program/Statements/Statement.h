#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include "Program/Operand.h"
#include "Program/Program.h"
#include <QJsonObject>
#include <iostream>
#include <sstream>
using namespace std;

class Statement {
    public:
        Statement() {}
        virtual ~Statement() {}
        virtual void run() {}
        virtual QJsonObject compile(string instr) { return QJsonObject(); }
};

class ReadStmt: public Statement {
    public:
        void run() override;
        QJsonObject compile(string instr) override;
};

class DeclIntStmt: public Statement {
    private:
        Operand varName;
    public:
        DeclIntStmt();
        DeclIntStmt(Operand in);
        void run() override;
        QJsonObject compile(string instr) override;
};

#endif
