#include "JEqualStmt.h"

JEqualStmt::JEqualStmt(Identifier* jump): jumpPos(jump) {}

void JEqualStmt::run(Program* program) {
    int jumpDestination = this->jumpPos.getIdentifier()->getValue();
    if (program->getComparison() == 0) {
        program->setIndex(jumpDestination-1);
    }
}

QJsonObject JEqualStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jeq"));
        statementObject.insert("jump_pos", QString::fromStdString(this->jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}
