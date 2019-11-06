#include "Program.h"
using namespace std;

//Compiles the input json.
void Program::compile() {
    ifstream file;
    string line;
    cout << "Opening file " << filename << ".\n";
    file.open(filename);
    if(file.is_open()) {
        cout << "File Opened.\n";
        QJsonObject jsonStats;
        QJsonObject jsonLabelIdentifiers;
        QJsonObject jsonVariableIdentifiers;
        int index = 0;
        while(getline(file, line)) {
            cout << index << " : " << line << "\n";
            //ADD SYNTAX CHECKER
            size_t words = 0;
            string* arr = splitString(line, words);
            Statement* stat;
            string firstarg = arr[0];
            int initialArg = 0;

            // Cuts the label out of the line and adds it to the list of identifiers as well as the line it exists at.
            if(firstarg.back() == ':') {
                line = line.erase(0, firstarg.length());
                firstarg.pop_back();
                jsonLabelIdentifiers.insert(QString::fromStdString(firstarg), index);
                firstarg = arr[1];
                initialArg++;
            }

            if(firstarg == "dci") {
                stat = new DeclIntStmt();
                jsonVariableIdentifiers.insert(QString::fromStdString(arr[initialArg+1]), 0);
            } else if(firstarg == "rdi") {
                stat = new DeclIntStmt();
            } else if(firstarg == "prt") {
                //work will have to go into whether this is a literal or string being printed.
                stat = new DeclIntStmt();
            } else if(firstarg == "cmp") {
                stat = new DeclIntStmt();
            } else if(firstarg == "jmr") {
                stat = new DeclIntStmt();
            } else if(firstarg == "jmp") {
                stat = new DeclIntStmt();
            } else if(firstarg == "end") {
                stat = new EndStmt();
            } else if(firstarg[0] == '#') {
                // Just a comment so skip the line.
                continue;
            } else {
                cout << "SYNTAX OF LINE INCORRECT: " << line;
                break;
            }

            jsonStats.insert(QString::number(index), stat->compile(line));
            index++;
        }
        QJsonObject compiled;
        QJsonObject identifiers;
        identifiers.insert("variables", jsonVariableIdentifiers);
        identifiers.insert("labels", jsonLabelIdentifiers);
        compiled.insert("identifiers", identifiers);
        compiled.insert("objects", jsonStats);

        QJsonDocument doc(compiled);
        string name = filename.substr(0, filename.length() - 3) + "json";
        char namestr[name.length()+1];
        name.copy(namestr, name.length()+1);
        namestr[name.length()] = '\0';

        QFile jsonFile(namestr);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(doc.toJson(QJsonDocument::Indented));

        file.close();
    }
}

void Program::execute() {

}

void Program::print() {

}

// cuts up a string of unknown size into parts.
string* Program::splitString(string str, size_t& size) {
    string toParse = str;

    size = 0;
    stringstream ssin(str);

    while(ssin >> str) {
        ++size;
    }

    string *arr = new string[size];
    stringstream ssin2(toParse);
    size_t i = 0;
    while (i < size){
        ssin2 >> arr[i];
        ++i;
    }

    return arr;
}

string* Program::splitString(string str) {
    string toParse = str;

    size_t size = 0;
    stringstream ssin(str);

    while(ssin >> str) {
        ++size;
    }

    string *arr = new string[size];
    stringstream ssin2(toParse);
    size_t i = 0;
    while (i < size){
        ssin2 >> arr[i];
        ++i;
    }

    return arr;
}
