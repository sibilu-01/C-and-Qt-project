#include "JEqualStmt.h"

JEqualStmt::JEqualStmt(Identifier* jump): jumpPos(jump) {}

void JEqualStmt::run(Program* program) {

}

QJsonObject JEqualStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(words == 2) {
        statementObject.insert("stmt", QString::fromStdString("jeq"));
        statementObject.insert("jump_pos", QString::fromStdString(jumpPos.getIdentifier()->getName()));
    }
    return statementObject;
}
