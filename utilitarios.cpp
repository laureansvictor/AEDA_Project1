//
// Created by laureano on 15/11/19.
//

#include "utilitarios.h"

void tokenize(string const &str, char delim, vector<string> &out) {
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }
}

//Read options of all my menus/moment of choices
int readOptions(
        const vector<string> &menu) // This functions take a string vector wich each position is an option then return this option
{
    int option;
    cout << ":::::::::::::::::::::::::::::::::::" << endl;
    cout << "             options             " << endl;
    cout << ":::::::::::::::::::::::::::::::::::" << endl;
    for (size_t i = 0; i < menu.size(); i++) {
        cout << i + 1 << " - " << menu.at(i) << endl;
    }
    cout << "0 - VOLTAR" << endl;
    option = readInteger(" : ");
    return option;
}


template<typename T>
istream &getInput(string prompt,
                  T &input) // this template of function help's me to get the information that i want showing a certain string (usualy a question)
{
    cin.clear();
    cout << prompt;
    return getline(cin, input);
}


int readInteger(string prompt) //responsible to readIntData
{
    string input;
    while (getInput(prompt, input) || cin.eof()) {
        istringstream is(input);
        int inputAsInt;
        if (is >> inputAsInt)
            return inputAsInt;
        cout << '"' << input << "\" is not valid." << endl;
    }
    // A failure from getInput means something outside the normal realm of events
    // for console input has occurred -- possibly stdin was redirected to a file,
    // and we ran into eof, for example.  Let's consider it exceptional.
    throw runtime_error("Unexpected extraction error in readInteger function\n");
}


double readDouble(string prompt) //responsible to readDouble data
{
    string input;
    while (getInput(prompt, input) || cin.eof()) {
        istringstream is(input);
        double inputAsDouble;
        if (is >> inputAsDouble)
            return inputAsDouble;
        cout << '"' << input << "\" is not valid." << endl;
    }
    // A failure from getInput means something outside the normal realm of events
    // for console input has occurred -- possibly stdin was redirected to a file,
    // and we ran into eof, for example.  Let's consider it exceptional.
    throw runtime_error("Unexpected extraction error in readDouble function\n");
}

string readString(string prompt) // responsible for string data
{
    string input;
    while (getInput(prompt, input) || cin.eof()) {
        istringstream is(input);
        string inputAsString;
        if (is >> inputAsString)
            return inputAsString;
        cout << '"' << input << "\" is not valid." << endl;
    }
    // A failure from getInput means something outside the normal realm of events
    // for console input has occurred -- possibly stdin was redirected to a file,
    // and we ran into eof, for example.  Let's consider it exceptional.
    throw runtime_error("Unexpected extraction error in readString function\n");
}
//ps* all of them help with the ctrl+z issue

void deleteFileToRewrite(string file) {
    std::ofstream ofs(file, std::ios::out | std::ios::trunc); // clear contents
    if (ofs.is_open()) {
    }
    ofs.close();
}
