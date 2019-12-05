#include "DeclArrayStmt.h"

DeclArrayStmt::DeclArrayStmt(Identifier* array): array(array) {}

void DeclArrayStmt::run(Program* program) {
    program->addIdentifier(this->array.getIdentifier());
    for(int i = 0; i < this->array.getIdentifier()->getValue(); i++)
        program->addIdentifier(dynamic_cast<Array*>(this->array.getIdentifier())->getValue(i));
}

QJsonObject DeclArrayStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 3) {
        statementObject.insert("stmt", QString::fromStdString("dca"));
        statementObject.insert("name", QString::fromStdString(this->array.getIdentifier()->getName()));
        if(this->array.getIdentifier()->getValue() == 0) {
            statementObject.insert("size", QString::fromStdString(dynamic_cast<Array*>(this->array.getIdentifier())->getArgName()));
        } else {
            statementObject.insert("size", this->array.getIdentifier()->getValue());
        }


        program->addIdentifier(this->array.getIdentifier());
        for(int i = 0; i < this->array.getIdentifier()->getValue(); i++)
            program->addIdentifier(dynamic_cast<Array*>(this->array.getIdentifier())->getValue(i));
    }
    return statementObject;
}
