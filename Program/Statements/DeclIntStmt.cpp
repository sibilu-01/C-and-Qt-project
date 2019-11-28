#include "DeclIntStmt.h"

DeclIntStmt::DeclIntStmt(Identifier* var): variable(var) {}

void DeclIntStmt::run(Program* program) {
    program->addIdentifier(variable.getIdentifier());
}

QJsonObject DeclIntStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("var", QString::fromStdString(variable.getIdentifier()->getName()));
        program->addIdentifier(variable.getIdentifier());
    }
    return statementObject;
}
