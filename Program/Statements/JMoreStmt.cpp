#include "JMoreStmt.h"

JMoreStmt::JMoreStmt(Identifier* jump): jumpPos(jump) {}

void JMoreStmt::run(Program* program) {
    int jumpDestination = jump->getValue();
    if (program->comparisonFlag == 1) {
        program->setIndex(jumpDestination);
    }
}

QJsonObject JMoreStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jmr"));
        statementObject.insert("jump_pos", QString::fromStdString(jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}
