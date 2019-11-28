#include "Operand.h"

Operand::Operand(Identifier* iden): identifier(iden) {
}

Identifier* Operand::getIdentifier() {
    return this->identifier;
}
