#include "PrtStmt.h"

PrtStmt::PrtStmt(std::string s): variable(s) {}

PrtStmt::PrtStmt(Identifier* ident): identifier(ident) {}

void PrtStmt::run(Program* program) {

}

QJsonObject PrtStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    if(words >= 2) { // Words 2 args or greater.
        if(variable.find('\"') != std::string::npos) {
            if(variable.front() == '\"' && variable.back() == '\"') {
                variable.erase(0, 1);
                variable.erase(variable.size() - 1);
                statementObject.insert("stmt", "prt");
                statementObject.insert("printlit", QString::fromStdString(variable));
            }
        } else if(identifier.getIdentifier() != nullptr) {
            statementObject.insert("stmt", "prt");
            statementObject.insert("printvar", QString::fromStdString(this->identifier.getIdentifier()->getName()));
        } else if(words == 2 && args[1].find_first_not_of("0123456789") == std::string::npos) {
            int i = stoi(args[1]);
            statementObject.insert("stmt", "prt");
            statementObject.insert("printlit", i);
        }
    }

    return statementObject;
}
