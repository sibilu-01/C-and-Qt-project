#include "MovStmt.h"

MovStmt::MovStmt(Identifier* varLeft, Identifier* varRight): variableLeft(varLeft), variableRight(varRight) {}

void MovStmt::run(Program* program) {
}

QJsonObject MovStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("mov"));
        statementObject.insert("lvar", QString::fromStdString(this->variableLeft.getIdentifier()->getName()));
        statementObject.insert("rvar", QString::fromStdString(this->variableRight.getIdentifier()->getName()));
    }
    return statementObject;
}
