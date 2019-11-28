#include "ReadStmt.h"

ReadStmt::ReadStmt(Identifier* var): variable(var) {}

void ReadStmt::run(Program* program) {
    
}

QJsonObject ReadStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(variable.getIdentifier() != nullptr && words == 2) {
        statementObject.insert("stmt", QString::fromStdString("rdi"));
        statementObject.insert("var", QString::fromStdString(variable.getIdentifier()->getName()));
    }
    return statementObject;
}
