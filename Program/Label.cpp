#include "Label.h"

Label::Label(std::string name, int index): Identifier(name), index_pos(index) {}

int Label::getValue() {
    return this->index_pos;
}
