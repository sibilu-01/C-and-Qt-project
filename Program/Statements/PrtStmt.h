#ifndef PRTSTMT_H
#define PRTSTMT_H
#include "Statement.h"

class PrtStmt: public Statement {
    private:
        std::string variable = "";
        Operand identifier = nullptr;
    public:
        PrtStmt(std::string toprint);
        PrtStmt(Identifier* ident);
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // PRTSTMT_H
