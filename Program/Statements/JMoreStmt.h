#ifndef JMORESTMT_H
#define JMORESTMT_H
#include "Statement.h"

class JMoreStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JMoreStmt(Identifier* jump);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // JMORESTMT_H
