#include "Statement.h"

EndStmt::EndStmt() {}

void EndStmt::run() {

}

QJsonObject EndStmt::compile(Program *program, string instr) {
    size_t words = 0;
    string *arr = Program::splitString(instr, words);

    QJsonObject statementObject;
    if(words == 1) {
        statementObject.insert("stmt", QString::fromStdString(arr[0]));
    } else {
        program->error_code = 1; // Syntax error
    }

    return statementObject;
}
