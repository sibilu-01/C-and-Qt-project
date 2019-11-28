#ifndef LABEL_H
#define LABEL_H
#include "Identifier.h"

class Label: public Identifier {
    private:
        int index_pos;
    public:
        Label(std::string name, int index);
        ~Label() override {}

        int getValue() override;
};

#endif // LABEL_H
