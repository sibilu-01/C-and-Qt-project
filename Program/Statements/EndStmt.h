#ifndef ENDSTMT_H
#define ENDSTMT_H
#include "Statement.h"

class EndStmt: public Statement {
    public:
        EndStmt();
        void run(Program*) override;
        QJsonObject compile(Program*, std::vector<std::string>) override;
};

#endif // ENDSTMT_H
