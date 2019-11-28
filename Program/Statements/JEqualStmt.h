#ifndef JEQUALSTMT_H
#define JEQUALSTMT_H
#include "Statement.h"

class JEqualStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JEqualStmt(Identifier* jump);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // JEQUALSTMT_H
