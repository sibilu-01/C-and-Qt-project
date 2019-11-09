#include "Statement.h"

PrtStmt::PrtStmt(string s): variable(s) {}

void PrtStmt::run() {

}

QJsonObject PrtStmt::compile(map<string, Identifier*> *identifiers, vector<string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    if(words >= 2) { // Words 2 args or greater.
        string print;
        for(size_t i = 1; i < words - 1; i++) {
            print.append(args[i] + " ");
        }
        print.append(args[words-1]); //Make our print string.

        if(print.front() == '\"' && print.back() == '\"') { // Check for quotes.
            statementObject.insert("stmt", "prt");
            statementObject.insert("prints", QString::fromStdString(print));
        } else if(words == 2) { // 2 words w no quotes means var print
            if(identifiers->find(args[1]) != identifiers->end()) {
                statementObject.insert("stmt", "prt");
                statementObject.insert("print", QString::fromStdString(identifiers->find(args[1])->second->getName()));
            }
        }
    }

    return statementObject;
}
