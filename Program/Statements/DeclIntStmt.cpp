#include "Statement.h"
#include "Program/Program.h"

DeclIntStmt::DeclIntStmt(): varName("") {}
DeclIntStmt::DeclIntStmt(Operand in): varName(in) {}

void DeclIntStmt::run() {

}

QJsonObject DeclIntStmt::compile(string instr) {
    string *arr = Program::splitString(instr);

    QJsonObject statementObject;
    statementObject.insert("stmt", QString::fromStdString(arr[0]));
    statementObject.insert("var", QString::fromStdString(arr[1]));

    return statementObject;
}
