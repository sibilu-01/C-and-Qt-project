#include "Operand.h"

Operand::Operand(Identifier* iden): identifier(iden) {
}

Operand::Operand(std::string name): identifier(new Identifier(name)) {
}

Operand::Operand(std::string name, int i): identifier(new Variable(name, i)) {
}

Operand::Operand(std::map<std::string, Identifier*> *identifiers, std::string name): identifier(identifiers->find(name)->second) {

}

Identifier* Operand::getIdentifier() {
    return this->identifier;
}
