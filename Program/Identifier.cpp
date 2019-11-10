#include "Identifier.h"

Identifier::Identifier(std::string name): name(name) {}

std::string Identifier::getName() {
    return this->name;
}

Variable::Variable(std::string name, int val): Identifier(name), value(val) {}

int Variable::getValue() {
    return this->value;
}

void Variable::setValue(int i) {
    this->value = i;
}

Label::Label(std::string name, int index): Identifier(name), index_pos(index) {}

int Label::getValue() {
    return this->index_pos;
}
