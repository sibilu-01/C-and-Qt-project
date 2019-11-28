#include "Variable.h"

Variable::Variable(std::string name): Identifier(name), value(0) {}
Variable::Variable(std::string name, int val): Identifier(name), value(val) {}

int Variable::getValue() {
    return this->value;
}

void Variable::setValue(int i) {
    this->value = i;
}
