#include "Statement.h"

EndStmt::EndStmt() {}

void EndStmt::run() {

}

QJsonObject EndStmt::compile(Program *program, vector<string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    if(words == 1) {
        statementObject.insert("stmt", QString::fromStdString("end"));
    } else {
        program->error_code = 1; // Syntax error
    }

    return statementObject;
}
