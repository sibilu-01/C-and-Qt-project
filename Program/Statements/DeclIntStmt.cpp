#include "Statement.h"

DeclIntStmt::DeclIntStmt(): varName("") {}
DeclIntStmt::DeclIntStmt(Operand in): varName(in) {}

void DeclIntStmt::run() {

}

QJsonObject DeclIntStmt::compile(Program *program, string instr) {
    size_t words = 0;
    string *arr = Program::splitString(instr, words);
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString(arr[0]));
        statementObject.insert("op1", QString::fromStdString(arr[1]));
        program->jsonVariableIdentifiers.insert(QString::fromStdString(arr[1]), 0);
    } else {
        program->error_code = 1;
    }

    return statementObject;
}
