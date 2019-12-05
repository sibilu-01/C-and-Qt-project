#include "PrtStmt.h"

PrtStmt::PrtStmt(std::string s): variable(s), type(false) {}

PrtStmt::PrtStmt(Identifier* ident): identifier(ident), type(true) {}


void PrtStmt::run(Program* program) {
    if(type) {
        emit program->print(QString::number(identifier.getIdentifier()->getValue()));
    } else {
        emit program->print(QString::fromStdString(variable));
    }
}

QJsonObject PrtStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    if(words >= 2) { // Words 2 args or greater.
        if(this->variable.find('\"') != std::string::npos) {
            if(this->variable.front() == '\"' && this->variable.back() == '\"') {
                this->variable.erase(0, 1);
                this->variable.erase(this->variable.size() - 1);
                statementObject.insert("stmt", "prt");
                statementObject.insert("print", QString::fromStdString(this->variable));
                statementObject.insert("type", true);
            }
        } else if(identifier.getIdentifier() != nullptr) {
            statementObject.insert("stmt", "prt");
            statementObject.insert("print", QString::fromStdString(this->identifier.getIdentifier()->getName()));
            statementObject.insert("type", true);
        } else if(words == 2 && args[1].find_first_not_of("0123456789") == std::string::npos) {
            int i = stoi(args[1]);
            statementObject.insert("stmt", "prt");
            statementObject.insert("print", i);
            statementObject.insert("type", false);
        }
    }

    return statementObject;
}
