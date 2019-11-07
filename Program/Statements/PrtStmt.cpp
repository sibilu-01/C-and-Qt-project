#include "Statement.h"

PrtStmt::PrtStmt() {}

void PrtStmt::run() {

}

QJsonObject PrtStmt::compile(Program *program, string instr) {
    size_t words = 0;
    string *arr = Program::splitString(instr, words);

    QJsonObject statementObject;
    if(words >= 2) { // Words 2 args or greater.
        string print;
        for(size_t i = 1; i < words - 1; i++) {
            print.append(arr[i] + " ");
        }
        print.append(arr[words-1]); //Make our print string.

        if(print.front() == '\"' && print.back() == '\"') { // Check for quotes.
            statementObject.insert("stmt", QString::fromStdString(arr[0]));
            statementObject.insert("printstr", QString::fromStdString(print));
        } else if(words == 2) { // 2 words means var print
            if(program->jsonVariableIdentifiers.contains(QString::fromStdString(arr[1]))) {
                statementObject.insert("stmt", QString::fromStdString(arr[0]));
                statementObject.insert("printvar", QString::fromStdString(arr[1]));
            } else {
                program->error_code = 2; //Var not found.
            }
        } else {
            program->error_code = 1; //Syntax error
        }

    } else {
        program->error_code = 1; //Syntax error
    }

    return statementObject;
}
