#include "Statement.h"

ReadStmt::ReadStmt(string varName): variable(Operand(varName)) {}

void ReadStmt::run() {

}

QJsonObject ReadStmt::compile(map<string, Identifier*> *identifiers, vector<string> args) {

}
