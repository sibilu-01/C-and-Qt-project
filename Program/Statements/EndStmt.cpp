#include "Statement.h"

EndStmt::EndStmt() {}

void EndStmt::run() {

}

QJsonObject EndStmt::compile(vector<string> args) {
    size_t words = args.size();

    QJsonObject statementObject;
    if(words == 1) {
        statementObject.insert("stmt", QString::fromStdString("end"));
    }

    return statementObject;
}
