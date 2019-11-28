#ifndef ADDSTMT_H
#define ADDSTMT_H
#include "Statement.h"

class AddStmt: public Statement {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        AddStmt(Identifier* variableLeft, Identifier* variableRight);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // ADDSTMT_H
