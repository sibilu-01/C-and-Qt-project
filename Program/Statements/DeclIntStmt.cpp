#include "DeclIntStmt.h"

DeclIntStmt::DeclIntStmt(Identifier* var): variable(var) {var->setValue(0);}

void DeclIntStmt::run(Program* program) {
    this->variable.getIdentifier()->setValue(0);
    program->addIdentifier(this->variable.getIdentifier());
}

QJsonObject DeclIntStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("var", QString::fromStdString(this->variable.getIdentifier()->getName()));
        program->addIdentifier(this->variable.getIdentifier());
    }
    return statementObject;
}
