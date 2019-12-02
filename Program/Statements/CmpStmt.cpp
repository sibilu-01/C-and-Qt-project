#include "CmpStmt.h"

CmpStmt::CmpStmt(Identifier* varLeft, Identifier* varRight): variableLeft(varLeft), variableRight(varRight) {}

void CmpStmt::run(Program* program) {
    if (this->variableLeft.getIdentifier()->getValue() > this->variableRight.getIdentifier()->getValue()) {
        program->setComparison(1);
    }else if (this->variableLeft.getIdentifier()->getValue() == this->variableRight.getIdentifier()->getValue()) {
        program->setComparison(0);
    }else {
        program->setComparison(-1);
    }
}

QJsonObject CmpStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("cmp"));
        statementObject.insert("lvar", QString::fromStdString(this->variableLeft.getIdentifier()->getName()));
        statementObject.insert("rvar", QString::fromStdString(this->variableRight.getIdentifier()->getName()));
    }
    return statementObject;
}
