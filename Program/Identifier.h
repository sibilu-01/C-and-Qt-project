#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

class Identifier {
    private:
        std::string name;
    public:
        Identifier(std::string name);
        virtual ~Identifier() {}

        virtual int getValue() {
            return 0;
        }

        std::string getName();
};

class Variable: public Identifier {
    private:
        int value;
    public:
        Variable(std::string name, int val);
        ~Variable() override {}

        int getValue() override;
        void setValue(int i);
};

class Label: public Identifier {
    private:
        int index_pos;
    public:
        Label(std::string name, int index);
        ~Label() override {}

        int getValue() override;
};

#endif
