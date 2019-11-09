#include <string>
#include "Operand.h"

Operand::Operand(string in): identifier(new Identifier(in)) {
}

Identifier* Operand::getIdentifier() {
    return this->identifier;
}
