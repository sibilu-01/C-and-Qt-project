#include "Statement.h"

CmpStmt::CmpStmt() {}

void CmpStmt::run() {

}

QJsonObject CmpStmt::compile(Program *program, string instr) {
    string *arr = Program::splitString(instr);

    QJsonObject statementObject;
    statementObject.insert("stmt", QString::fromStdString(arr[0]));
    statementObject.insert("op1", QString::fromStdString(arr[1]));
    statementObject.insert("op2", QString::fromStdString(arr[2]));
    program->jsonVariableIdentifiers.insert(QString::fromStdString(arr[1]), 0);
    program->jsonVariableIdentifiers.insert(QString::fromStdString(arr[2]), 0);

    return statementObject;
}
