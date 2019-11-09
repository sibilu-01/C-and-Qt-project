#include "Statement.h"

DeclIntStmt::DeclIntStmt(string varName): variable(Operand(varName)) {}

void DeclIntStmt::run() {

}

QJsonObject DeclIntStmt::compile(Program *program, vector<string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        program->addIdentifier(variable.getIdentifier());

        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("op1", QString::fromStdString(variable.getIdentifier()->getName()));
    } else {
        program->error_code = 1;
    }
    return statementObject;
}
