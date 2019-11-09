#include "Statement.h"

DeclIntStmt::DeclIntStmt(map<string, Identifier*> *identifiers, string varName): variable(varName, 0) {
    identifiers->insert(pair<string, Identifier*>(variable.getIdentifier()->getName(), variable.getIdentifier()));
}

void DeclIntStmt::run() {

}

QJsonObject DeclIntStmt::compile(vector<string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("var", QString::fromStdString(variable.getIdentifier()->getName()));
    }
    return statementObject;
}
