#include "DeclArrayStmt.h"

DeclArrayStmt::DeclArrayStmt(Identifier* array): array(array) {}

void DeclArrayStmt::run(Program* program) {
    program->addIdentifier(array.getIdentifier());
}

QJsonObject DeclArrayStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("name", QString::fromStdString(array.getIdentifier()->getName()));
        statementObject.insert("size", array.getIdentifier()->getValue());
        program->addIdentifier(array.getIdentifier());
    }
    return statementObject;
}
