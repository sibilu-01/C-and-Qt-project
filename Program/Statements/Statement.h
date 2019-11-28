#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <QJsonObject>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "Program/Operand.h"
#include "Program/Identifier.h"
#include "Program/Variable.h"
#include "Program/Label.h"
#include "Program/Array.h"
#include "Program/Program.h"

class Statement {
    public:
        virtual ~Statement() {}
        virtual void run(Program*) = 0;
        virtual QJsonObject compile(Program*, std::vector<std::string>) = 0;
        Statement() {}
};

#endif // STATEMENT_H
