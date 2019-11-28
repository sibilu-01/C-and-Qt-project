#include "Array.h"

Array::Array(std::string name, int size): Identifier(name), size(size) {}

int Array::getValue(int index) {
    if(index < size) {
        return this->variables.at(size_t(index));
    } else {
        return 0;
    }
}

void Array::setValue(int index, int value) {
    this->variables.assign(size_t(index), value);
}

int Array::getValue() {
    return this->size;
}
