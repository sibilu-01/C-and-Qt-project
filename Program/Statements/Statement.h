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

class Statement {
    public:
        virtual ~Statement() {}
        virtual void run() = 0;
        virtual QJsonObject compile(std::vector<std::string> args) = 0;
        Statement() {}
};

class ReadStmt: public Statement {
    private:
        Operand variable;
    public:
        ReadStmt(Identifier* var);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class DeclIntStmt: public Statement {
    private:
        Operand variable;
        std::map<std::string, Identifier*>* identifiers;
    public:
        DeclIntStmt(std::map<std::string, Identifier*> *identifiers, std::string varName);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class EndStmt: public Statement {
    public:
        EndStmt();
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class PrtStmt: public Statement {
    private:
        std::string variable = "";
        Operand identifier = nullptr;
    public:
        PrtStmt(std::string toprint);
        PrtStmt(Identifier* ident);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class CmpStmt: public Statement {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        CmpStmt(Identifier* variableLeft, Identifier* variableRight);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class JMoreStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JMoreStmt(Identifier* jump);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class JumpStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JumpStmt(Identifier* jump);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class JLessStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JLessStmt(Identifier* jump);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
}

class JEqualStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JEqualStmt(Identifier* jump);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
}

class AddStmt: public AddStmt {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        AddStmt(Identifier* variableLeft, Identifier* variableRight);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};

class MovStmt: public Statement {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        MovStmt(Identifier* variableLeft, Identifier* variableRight);
        void run() override;
        QJsonObject compile(std::vector<std::string> args) override;
};
#endif
