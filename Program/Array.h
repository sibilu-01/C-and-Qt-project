#ifndef ARRAY_H
#define ARRAY_H
#include "Identifier.h"

class Array: public Identifier {
    private:
        int size;
        std::vector<int> variables;
    public:
        Array(std::string, int size);
        ~Array() override {}

        int getValue() override;
        int getValue(int index);
        void setValue(int index, int var);
};

#endif // ARRAY_H
