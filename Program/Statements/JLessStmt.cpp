#include "JLessStmt.h"

JLessStmt::JLessStmt(Identifier* jump): jumpPos(jump) {}

void JLessStmt::run(Program* program) {
    int jumpDestination = this->jumpPos.getIdentifier()->getValue();
    if (program->getComparison() == -1) {
        program->setIndex(jumpDestination);
    }
}

QJsonObject JLessStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jls"));
        statementObject.insert("jump_pos", QString::fromStdString(this->jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}
