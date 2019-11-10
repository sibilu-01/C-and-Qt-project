#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>
using namespace std;

class Identifier {
    private:
        string name;
    public:
        Identifier(string name);
        virtual ~Identifier() {}

        virtual int getValue() {
            return 0;
        }

        string getName();
};

class Variable: public Identifier {
    private:
        int value;
    public:
        Variable(string name, int val);
        ~Variable() override {}

        int getValue() override;
        void setValue(int i);
};

class Label: public Identifier {
    private:
        int index_pos;
    public:
        Label(string name, int index);
        ~Label() override {}

        int getValue() override;
};

#endif
