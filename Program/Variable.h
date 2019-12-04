#ifndef VARIABLE_H
#define VARIABLE_H
#include "Identifier.h"

class Variable: public Identifier {
    private:
        int value;
    public:
        Variable(std::string);
        Variable(std::string, int);
        ~Variable() override {}

        int getValue() override;
        void setValue(int i) override;
};

#endif // VARIABLE_H
