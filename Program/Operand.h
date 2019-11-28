#ifndef OPERAND_H
#define OPERAND_H

#include "Program/Identifier.h"
#include "Program/Variable.h"
#include "Program/Array.h"
#include "Program/Label.h"
#include <string>
#include <map>

class Operand {
    private:
        Identifier* identifier;
    public:
        Operand(Identifier* iden);
        Identifier* getIdentifier();
};

#endif
