#include "Statement.h"

ReadStmt::ReadStmt() {}
void ReadStmt::run() {

}

QJsonObject ReadStmt::compile(Program *program, string instr) {
    string *arr = Program::splitString(instr);

    QJsonObject statementObject;
    statementObject.insert("stmt", QString::fromStdString(arr[0]));
    statementObject.insert("op1", QString::fromStdString(arr[1]));
    program->jsonVariableIdentifiers.insert(QString::fromStdString(arr[1]), 0);

    return statementObject;
}
