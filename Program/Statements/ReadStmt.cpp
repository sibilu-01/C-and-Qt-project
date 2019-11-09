#include "Statement.h"

ReadStmt::ReadStmt(string varName): variable(Operand(varName)) {}

void ReadStmt::run() {

}

QJsonObject ReadStmt::compile(Program *program, vector<string> args) {

}
