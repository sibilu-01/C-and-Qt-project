#include "DeclArrayStmt.h"

DeclArrayStmt::DeclArrayStmt(Identifier* array): array(array) {}

void DeclArrayStmt::run(Program* program) {
    program->addIdentifier(this->array.getIdentifier());
}

QJsonObject DeclArrayStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("name", QString::fromStdString(this->array.getIdentifier()->getName()));
        statementObject.insert("size", this->array.getIdentifier()->getValue());
        program->addIdentifier(this->array.getIdentifier());
    }
    return statementObject;
}
