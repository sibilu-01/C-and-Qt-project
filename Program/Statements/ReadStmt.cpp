#include "ReadStmt.h"
#include <QEventLoop>

ReadStmt::ReadStmt(Identifier* var): variable(var) {}

void ReadStmt::run(Program* program) {
    if(program->is_number(program->getInput()))
        variable.getIdentifier()->setValue(std::stoi(program->getInput()));
}

QJsonObject ReadStmt::compile(Program* program, std::vector<std::string> args) {
    size_t words = args.size();
    QJsonObject statementObject;
    if(this->variable.getIdentifier() != nullptr && words == 2) {
        statementObject.insert("stmt", QString::fromStdString("rdi"));
        statementObject.insert("var", QString::fromStdString(this->variable.getIdentifier()->getName()));
    }
    return statementObject;
}
