#ifndef CMPSTMT_H
#define CMPSTMT_H
#include "Statement.h"

class CmpStmt: public Statement {
    private:
        Operand variableLeft;
        Operand variableRight;
    public:
        CmpStmt(Identifier* variableLeft, Identifier* variableRight);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // CMPSTMT_H
