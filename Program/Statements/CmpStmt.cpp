#include "Statement.h"

CmpStmt::CmpStmt(Identifier* varLeft, Identifier* varRight): variableLeft(varLeft), variableRight(varRight) {}

void CmpStmt::run() {

}

QJsonObject CmpStmt::compile(std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("cmp"));
        statementObject.insert("lvar", QString::fromStdString(variableLeft.getIdentifier()->getName()));
        statementObject.insert("rvar", QString::fromStdString(variableRight.getIdentifier()->getName()));
    }
    return statementObject;
}
