#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>
#include "Menu.h"

using namespace std;

class Automaton {
    public:
        struct Transition {
            string origen_id;
            string destination_id;
            char destination_symbol;
        }; typedef vector<Transition> Transitions;

        vector<string> states;
        vector<char> symbols;
        Transitions transition_table;
        string initial_state;
        vector<string> final_states;
        string current_state;

        Automaton ();

        void print_states ();
        void print_symbols ();
        void print_initial ();
        void print_finals ();
        void print_transitions ();
        void print_automaton ();
        string return_transition (string current_state, char symbol);
        bool is_final (string state_id);
        bool check_string (string str);
        Transitions set_transition_table (vector<string> states, vector<char> symbols);
};

#endif