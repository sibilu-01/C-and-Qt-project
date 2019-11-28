#include "Identifier.h"

Identifier::Identifier(std::string name): name(name) {}

std::string Identifier::getName() {
    return this->name;
}
