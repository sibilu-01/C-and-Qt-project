#include "Statement.h"

AddStmt::AddStmt(Identifier* varLeft, Identifier* varRight): variableLeft(varLeft), variableRight(varRight) {}

void AddStmt::run() {

}

QJsonObject AddStmt::compile(std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("add"));
        statementObject.insert("lvar", QString::fromStdString(variableLeft.getIdentifier()->getName()));
        statementObject.insert("rvar", QString::fromStdString(variableRight.getIdentifier()->getName()));
    }
    return statementObject;
}
