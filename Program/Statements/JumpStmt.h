#ifndef JUMPSTMT_H
#define JUMPSTMT_H
#include "Statement.h"

class JumpStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JumpStmt(Identifier* jump);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // JUMPSTMT_H
