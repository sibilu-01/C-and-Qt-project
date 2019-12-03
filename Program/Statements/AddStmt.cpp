#include "AddStmt.h"

AddStmt::AddStmt(Identifier* varLeft, Identifier* varRight): variableLeft(varLeft), variableRight(varRight) {}

void AddStmt::run(Program* program) {
      int sum = variableLeft.getIdentifier()->getValue() + variableRight.getIdentifier()->getValue();
      variableRight.getIdentifier()->setValue(sum);
}

QJsonObject AddStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("add"));
        statementObject.insert("lvar", QString::fromStdString(this->variableLeft.getIdentifier()->getName()));
        statementObject.insert("rvar", QString::fromStdString(this->variableRight.getIdentifier()->getName()));
    }
    return statementObject;
}
