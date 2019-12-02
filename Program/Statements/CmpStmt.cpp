#include "CmpStmt.h"

CmpStmt::CmpStmt(Identifier* varLeft, Identifier* varRight): variableLeft(varLeft), variableRight(varRight) {}

void CmpStmt::run(Program* program) {
    if (varLeft->getValue() > varRight->getValue()) {
        program->setComparisonFlag(1);
    }else if (varLeft->getValue() == varRight->getValue()) {
        program->setComparisonFlag(0);
    }else {
        program->setComparisonFlag(-1);
    }
}

QJsonObject CmpStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("cmp"));
        statementObject.insert("lvar", QString::fromStdString(variableLeft.getIdentifier()->getName()));
        statementObject.insert("rvar", QString::fromStdString(variableRight.getIdentifier()->getName()));
    }
    return statementObject;
}
