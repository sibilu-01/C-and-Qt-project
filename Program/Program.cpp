#include "Program.h"
using namespace std;

//Compiles the input json.
void Program::compile() {
    ifstream file;
    string line;
    cout << "Opening file " << filename << ".\n";
    file.open(filename);
    if(file.is_open()) {
        error_code = 0;
        cout << "File Opened.\n";
        int index = 0;
        int linenum = 0;
        while(getline(file, line)) {
            cout << index << " : " << line << "\n";
            //ADD SYNTAX CHECKER
            size_t words = 0;
            string* arr = splitString(line, words);
            string firstarg = arr[0];

            // Cuts the label out of the line and adds it to the list of identifiers as well as the line it exists at.
            if(firstarg.back() == ':') {
                line = line.erase(0, firstarg.length());
                firstarg.pop_back();
                jsonLabelIdentifiers.insert(QString::fromStdString(firstarg), index);
                firstarg = arr[1];
                words++;
            }

            Statement* stat;
            if(firstarg == "dci") {
                stat = new DeclIntStmt();
            } else if(firstarg == "rdi") {
                stat = new ReadStmt();
            } else if(firstarg == "prt") {
                stat = new PrtStmt();
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
                error_code = 1; // Syntax error
                break;
            }

            QJsonObject statementObject = stat->compile(this, line);
            if(!statementObject.empty()) {
                jsonStats.insert(QString::number(index), statementObject);
                index++;
            } else {
                break;
            }
            linenum++;
        }
        if(error_code == 0) {
            QJsonObject compiled;
            QJsonObject identifiers;
            identifiers.insert("variables", jsonVariableIdentifiers);
            identifiers.insert("labels", jsonLabelIdentifiers);
            compiled.insert("identifiers", identifiers);
            compiled.insert("objects", jsonStats);
            compiled.insert("index", index);

            QJsonDocument doc(compiled);
            string name = filename.substr(0, filename.find(".")) + ".json";
            char namestr[name.length()+1];
            name.copy(namestr, name.length()+1);
            namestr[name.length()] = '\0';

            QFile jsonFile(namestr);
            jsonFile.open(QFile::WriteOnly);
            jsonFile.write(doc.toJson(QJsonDocument::Indented));
        } else if(error_code == 1) {
            //Report syntax error
        } else if(error_code == 2) {
            //Report VarNotFound error
        }
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
