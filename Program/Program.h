#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>



// Identifiers
#include "Program/Identifier.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>
#include <iterator>
#include <map>
#include <rundialog.h>
#include <QEventLoop>

class Statement;
class Program: public QObject {
    Q_OBJECT
    private:
        std::map<std::string, Identifier*> identifier;
        std::map<int, Statement*> statements;
        std::string filename;
        int comparisonFlag = 3;
        int error_code = 0;
        int index = 0;
        bool executing = false;
        std::string lastinput = "null";
    public:
        Program();
        Program(std::string);
        ~Program();
        bool is_number(std::string);
        std::vector<std::string> splitString(std::string);
        std::string compile();

        Identifier* getIdentifier(std::string);
        bool identifierExists(std::string);
        void addIdentifier(Identifier*);

        void setIndex(int);

        std::string getInput();

        int getComparison();
        void setComparison(int);

        bool getExecuting();
        void setExecuting(bool);

        Statement* getStatement(int);
        void addStatement(int, Statement*);


   public slots:
        void execute();
        void input(QString);

   signals:
        void print(QString);
        void inputRecieved();
};

#endif
