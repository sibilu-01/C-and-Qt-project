#ifndef JLESSSTMT_H
#define JLESSSTMT_H
#include "Statement.h"

class JLessStmt: public Statement {
    private:
        Operand jumpPos;
    public:
        JLessStmt(Identifier* jump);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // JLESSSTMT_H
