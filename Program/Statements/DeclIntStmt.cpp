#include "Statement.h"

DeclIntStmt::DeclIntStmt(std::map<std::string, Identifier*> *identifiers, std::string varName): variable(varName, 0), identifiers(identifiers) {}

void DeclIntStmt::run() {
    identifiers->insert(std::pair<std::string, Identifier*>(variable.getIdentifier()->getName(), variable.getIdentifier()));
}

QJsonObject DeclIntStmt::compile(std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("dci"));
        statementObject.insert("var", QString::fromStdString(variable.getIdentifier()->getName()));
        identifiers->insert(std::pair<std::string, Identifier*>(variable.getIdentifier()->getName(), variable.getIdentifier()));
    }
    return statementObject;
}
