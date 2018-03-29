#include <iostream> 
#include <vector>
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int states_amount, productions_amount;
string string_eval;

struct Production {
    vector<char> symbols;
    char destination;
};

struct State {
    int id;
    char state_name;
    vector<Production> productions;
};

vector<State> cfg_states;
int string_ptr = 0;
struct State current_state;

bool evaluate_production (struct Production production);
bool is_terminal (char name);

void initialize_cfg () {
    system("clear");
    cout << "Non terminal states amount: " << endl;
    cin >> states_amount;

    for (int i = 0; i < states_amount; i++) {
        struct State new_state;
        system("clear");
        cout << "Please enter the state name: " << endl;
        cin >> new_state.state_name;
        new_state.id = (i + 1);

        cout << "Please enter the amount of productions: " << endl;
        cin >> productions_amount;
        
        for (int j = 0; j < productions_amount; j++) {
            struct Production create_production;
            create_production.destination = ' ';
            string new_production;
            cout << "Please enter the production: " << endl; 
            cin >> new_production; 
            for (int k = 0; k < new_production.size(); k++) {
                if (is_terminal (new_production[k]))
                    create_production.symbols.push_back (new_production[k]);
                else {
                    create_production.destination = new_production[k];
                }
            }
            new_state.productions.push_back (create_production);
        }
        cfg_states.push_back (new_state);
    }
}

void print_cfg () {
    for (int i = 0; i < cfg_states.size(); i++) {
        cout << cfg_states[i].state_name << " -> ";
        
        for (int j = 0; j < cfg_states[i].productions.size(); j++) {
            if (j != 0)
                cout << "    |";
            for (int k = 0; k < cfg_states[i].productions[j].symbols.size(); k++) {
                cout << cfg_states[i].productions[j].symbols[k];
            }
            
            cout << cfg_states[i].productions[j].destination << endl;
        }
    }
}

int search_state (char name) {
    for (int i = 0; i < cfg_states.size(); i++) {
        if (cfg_states[i].state_name == name)
            return i;
    }
    return -1;
}

bool is_terminal (char name) {
    return islower (name);
}

void to_string (const string &file_name) {
	ifstream file (file_name.c_str());

	if (!file.is_open())
		throw "Error opening file";

	string line;
	string evaluation = "";
	while (getline(file, line)) {
		evaluation = evaluation + line;
	}

	string_eval = evaluation;
    cout << string_eval << endl;
}

bool evaluate_state () {
    if (string_ptr >= (string_eval.size()))
        return true;
    
    for (int i = 0; i < current_state.productions.size(); i++) {
        cout << "Production number" << i << endl;
        if (evaluate_production (current_state.productions[i]))
            return true;
    }
    return false;
}

bool evaluate_production (struct Production production) {
    int perserve_ptr = string_ptr;

    if (string_ptr >= (string_eval.size()))
        return true;

    for (int i = 0; i < production.symbols.size(); i++) {
        if (production.symbols[i] == string_eval[string_ptr]) {
            string_ptr++;
        } else {
            string_ptr = perserve_ptr;
            return false;
        }
    }
    cout << production.destination << endl;
    if (production.destination != ' ') {
        int id = search_state(production.destination);
        cout << id << endl;
        current_state = cfg_states[id];
        return evaluate_state ();
    }

    return true;
}



int main () { 
    initialize_cfg ();
    print_cfg ();
    to_string ("data.txt");
    current_state = cfg_states[0];
    if (evaluate_state () && string_ptr >= (string_eval.size()))
        cout << "El lenguaje cumple con el automata" << endl;
    else
        cout << "El lenguaje no cumple con el automatar" << endl;
}