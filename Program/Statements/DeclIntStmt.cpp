#include "Statement.h"

DeclIntStmt::DeclIntStmt(string varName): variable(Operand(varName)) {}

void DeclIntStmt::run() {

}

QJsonObject DeclIntStmt::compile(map<string, Identifier*> *identifiers, vector<string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        identifiers->insert(pair<string, Identifier*>(variable.getIdentifier()->getName(), variable.getIdentifier()));

        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("op1", QString::fromStdString(variable.getIdentifier()->getName()));
    }
    return statementObject;
}
