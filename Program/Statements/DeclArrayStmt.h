#ifndef DECLARRAYSTMT_H
#define DECLARRAYSTMT_H
#include "Statement.h"

class DeclArrayStmt: public Statement {
    private:
        Operand array;
    public:
        DeclArrayStmt(Identifier*);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // DECLARRAYSTMT_H
