#include "Automaton.h"
#include <fstream>

using namespace std;

int main () {
    Automaton atm = Automaton ();
    atm.print_automaton ();
    string mystring;
    ifstream myReadFile;

    myReadFile.open("text.txt");

    if (myReadFile.is_open()) {
        char output[100];
        while (!myReadFile.eof()) {
            myReadFile >> output;
            mystring = mystring + output;
        }
    }

    myReadFile.close();

    cout << endl;
    
    if (atm.check_string(mystring)) {
        cout << "El archivo cumple con el automata!" << endl;
    } else {
        cout << "El archivo no cumple con el automata!" << endl;
    }

    return 0;
}


