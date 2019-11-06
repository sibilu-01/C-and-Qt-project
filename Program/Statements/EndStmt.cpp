#include "Statement.h"

EndStmt::EndStmt() {}

void EndStmt::run() {

}

QJsonObject EndStmt::compile(Program *program, string instr) {
    string *arr = Program::splitString(instr);

    QJsonObject statementObject;
    statementObject.insert("stmt", QString::fromStdString(arr[0]));

    return statementObject;
}
