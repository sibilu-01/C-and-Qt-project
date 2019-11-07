#include "Statement.h"

PrtStmt::PrtStmt() {}

void PrtStmt::run() {

}

QJsonObject PrtStmt::compile(Program *program, string instr) {
    size_t words = 0;
    string *arr = Program::splitString(instr, words);

    QJsonObject statementObject;
    if(words >= 2) {
        string print;
        for(size_t i = 1; i < words - 1; i++) {
            print.append(arr[i] + " ");
        }
        print.append(arr[words-1]);

        if(print.front() == '\"' && print.back() == '\"') {
            statementObject.insert("stmt", QString::fromStdString(arr[0]));
            statementObject.insert("printstr", QString::fromStdString(print));
        } else if(words == 2) {
            if(program->jsonVariableIdentifiers.contains(QString::fromStdString(arr[1]))) {
                statementObject.insert("stmt", QString::fromStdString(arr[0]));
                statementObject.insert("printvar", QString::fromStdString(arr[1]));
            } else {
                string warning = "VARIABLE ERROR AT: " + instr + ".\nVariable does not exist.";
            }
        } else {
            string warning = "SYNTAX ERROR AT: " + instr;
        }

    } else {
        //throw program warning.
        string warning = "SYNTAX ERROR AT: " + instr;
    }

    return statementObject;
}
