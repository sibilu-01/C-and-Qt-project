#include "Statement.h"

JlessStmt::JlessStmt(Identifier* jump): jumpPos(jump) {}

void JlsStmt::run() {

}

QJsonObject JlessStmt::compile(std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jls"));
        statementObject.insert("jump_pos", QString::fromStdString(jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}