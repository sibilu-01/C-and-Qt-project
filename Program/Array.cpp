#include "Array.h"

Array::Array(std::string name, int size): Identifier(name), arr_size(new Variable(std::to_string(size), size)) {
    for(size_t i = 0; i < size_t(size); i++) {
        this->variables.push_back(new Variable("$" + name + "+" + std::to_string(i)));
    }
}

Array::Array(std::string name, Identifier* size): Identifier(name), arr_size(size) {
    for(size_t i = 0; i < size_t(size->getValue()); i++) {
        this->variables.push_back(new Variable("$" + name + "+" + std::to_string(i)));
    }
}

Variable* Array::getValue(int index) {
    if(index < this->arr_size->getValue()) {
        return this->variables.at(size_t(index));
    } else {
        return nullptr;
    }
}

void Array::setValue(int index, int value) {
    this->variables.assign(size_t(index), new Variable(std::to_string(value), value));
}

std::string Array::getArgName() {
    return this->arr_size->getName();
}

void Array::setValue(int index) {
    return;
}

int Array::getValue() {
    return int(this->variables.size());
}
