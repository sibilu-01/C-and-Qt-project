#include "Statement.h"

PrtStmt::PrtStmt(string s): variable(s) {}

PrtStmt::PrtStmt(Identifier* ident): identifier(ident) {}

void PrtStmt::run() {

}

QJsonObject PrtStmt::compile(vector<string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    statementObject.insert("stmt", "prt");
    if(words >= 2) { // Words 2 args or greater.
        if(variable.front() == '\"' && variable.back() == '\"') {
            variable.erase(0, 1);
            variable.erase(variable.size() - 1);
            statementObject.insert("printlit", QString::fromStdString(variable));
        } else if(identifier.getIdentifier() != nullptr) {
            statementObject.insert("printvar", QString::fromStdString(this->identifier.getIdentifier()->getName()));
        } else if(words == 2 && args[1].find_first_not_of("0123456789") == std::string::npos) {
            int i = stoi(args[1]);
            statementObject.insert("printlit", i);
        }
    }

    return statementObject;
}
