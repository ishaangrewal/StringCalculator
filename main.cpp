#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    string input;
    getline(cin, input);
    while(input != "quit" && input != "q") {
        string lhs;
        string rhs;
        string operation;
        std::istringstream infoISS(input);
        infoISS >> lhs;
        infoISS >> operation;
        infoISS >> rhs;
        cout << ">>" << endl;
        cout << "ans =" << endl;
        cout << endl;
        if (operation == "+") {
            cout << "    " <<add(lhs, rhs)<< endl;
        }
        else if(operation == "-") {
            cout << "    " << subtract(lhs, rhs) << endl;
        }
        else if(operation == "*") {
            cout << "    " <<multiply(lhs, rhs) << endl;
        }
        cout << endl;
        getline(cin, input);
    }
    cout << ">>" << endl;
    cout << "farvel!" << endl;
    // TODO(student): implement the UI
}

