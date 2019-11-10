#include "Statement.h"

JumpStmt::JumpStmt(Identifier* jump): jumpPos(jump) {}

void JumpStmt::run() {

}

QJsonObject JumpStmt::compile(std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jmp"));
        statementObject.insert("jump_pos", QString::fromStdString(jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}
