#ifndef READSTMT_H
#define READSTMT_H
#include "Statement.h"

class ReadStmt: public Statement {
    private:
        Operand variable;
    public:
        ReadStmt(Identifier* var);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // READSTMT_H
