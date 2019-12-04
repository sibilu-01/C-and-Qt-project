#ifndef ARRAY_H
#define ARRAY_H
#include "Identifier.h"
#include "Variable.h"

class Array: public Identifier {
    private:
        int arr_size;
        std::vector<Variable*> variables;
    public:
        Array(std::string, int size);
        ~Array() override {}

        int getValue() override;
        Variable* getValue(int index);
        void setValue(int index, int var);
        void setValue(int index) override;
};

#endif // ARRAY_H
