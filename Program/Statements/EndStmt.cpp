#include "EndStmt.h"

EndStmt::EndStmt() {}

void EndStmt::run(Program* program) {
}

QJsonObject EndStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    if(words == 1) {
        statementObject.insert("stmt", QString::fromStdString("end"));
    }

    return statementObject;
}
