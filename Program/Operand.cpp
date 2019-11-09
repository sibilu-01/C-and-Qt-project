#include <string>
#include "Operand.h"

Operand::Operand(Identifier* iden): identifier(iden) {
}

Operand::Operand(string name): identifier(new Identifier(name)) {
}

Operand::Operand(string name, int i): identifier(new Variable(name, i)) {
}

Operand::Operand(map<string, Identifier*> *identifiers, string name): identifier(identifiers->find(name)->second) {

}

Identifier* Operand::getIdentifier() {
    return this->identifier;
}
