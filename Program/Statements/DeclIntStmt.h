#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H
#include "Statement.h"

class DeclIntStmt: public Statement {
    private:
        Operand variable;
    public:
        DeclIntStmt(Identifier*);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // DECLINTSTMT_H
