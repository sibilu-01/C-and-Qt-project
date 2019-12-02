#include "JumpStmt.h"

JumpStmt::JumpStmt(Identifier* jump): jumpPos(jump) {}

void JumpStmt::run(Program* program) {
    int jumpDestination = this->jumpPos.getIdentifier()->getValue();
    program->setIndex(jumpDestination);
}

QJsonObject JumpStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jmp"));
        statementObject.insert("jump_pos", QString::fromStdString(this->jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}
