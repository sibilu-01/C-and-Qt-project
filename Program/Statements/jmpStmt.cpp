#include "Statement.h"

jmpStmt::jmpStmt(): varName("") {}
jmpStmt::jmpStmt(Operand in): varName(in) {}

void jmpStmt::run() {

}

QJsonObject jmpStmt::compile(Program *program, string instr) {
    string *arr = Program::splitString(instr);

    QJsonObject statementObject;
    statementObject.insert("stmt", QString::fromStdString(arr[0]));
    statementObject.insert("op1", QString::fromStdString(arr[1]));
    program->jsonVariableIdentifiers.insert(QString::fromStdString(arr[1]), 0);

    return statementObject;
}