#include "Statement.h"

DeclIntStmt::DeclIntStmt(): varName("") {}
DeclIntStmt::DeclIntStmt(Operand in): varName(in) {}

void DeclIntStmt::run() {

}

QJsonObject DeclIntStmt::compile(string instr) {
    string *arr = new string[2];
    stringstream ssin(instr);
    int i = 0;
    while (i < 2){
        ssin >> arr[i];
        ++i;
    }

    QJsonObject statementObject;
    statementObject.insert("stmt", QString::fromStdString(arr[0]));
    statementObject.insert("var", QString::fromStdString(arr[1]));


    return statementObject;
}
