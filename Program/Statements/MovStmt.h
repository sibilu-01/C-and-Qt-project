#ifndef MOVSTMT_H
#define MOVSTMT_H
#include "Statement.h"

class MovStmt: public Statement {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        MovStmt(Identifier* variableLeft, Identifier* variableRight);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // MOVSTMT_H
