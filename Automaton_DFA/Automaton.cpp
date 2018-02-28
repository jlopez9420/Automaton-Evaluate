#include "Automaton.h"

Automaton::Automaton () {
    this->states = get_states ();
    this->symbols = get_symbols ();
    this->initial_state = get_initial ();
    this->final_states = get_finals ();
    this->transition_table = set_transition_table (this->states, this->symbols);
    this->current_state = initial_state;
}

Automaton::Transitions Automaton::set_transition_table (vector<string> states, vector<char> symbols) {
    vector<string> destinations = get_transitions (states, symbols);
    Transitions trs_table;
    int k = 0;

    for (int i = 0; i < states.size(); i++) {
        for (int j = 0; j < symbols.size(); j++) {
            Transition trs;
            trs.origen_id = states[i];
            trs.destination_symbol = symbols[j];
            trs.destination_id = destinations[k];
            trs_table.push_back(trs);
            k++;
        }
    }

    return trs_table;
}

void Automaton::print_states () {
    cout << "{ ";

    for (int i = 0; i < this->states.size(); i++) {
        cout << this->states[i];
        if (i != (this->states.size() - 1))
            cout << ", ";
    }

    cout << " }";
}

void Automaton::print_symbols () {
    cout << "{ ";

    for (int i = 0; i < this->symbols.size(); i++) {
        cout << this->symbols[i] << ", ";
        if (i != (this->symbols.size() - 1))
            cout << ", ";
    }

    cout << " }";
}

void Automaton::print_initial () {
    cout << this->initial_state;
}

void Automaton::print_finals () {
    cout << "{ ";

    for (int i = 0; i < this->final_states.size(); i++) {
        cout << this->final_states[i] << ", ";
        if (i != (this->final_states.size() - 1))
            cout << ", ";
    }

    cout << " }";
}

void Automaton::print_transitions () {
    cout << "Origin - Symbol - Destination" << endl;
    for (int i = 0; i < this->transition_table.size(); i++) {
        cout << this->transition_table[i].origen_id << "       " << this->transition_table[i].destination_symbol << "       " << this->transition_table[i].destination_id << endl;
    }
}

void Automaton::print_automaton () {
    system ("clear");

    cout << "M = ("; print_states (); cout << ", "; print_symbols (); cout << ", "; print_initial (); cout << ", "; print_finals (); cout << ")" << endl << endl;
    print_transitions ();
}

bool Automaton::is_final (string state_id) {
    for (int i = 0; i < this->final_states.size(); i++) {
        if (final_states[i] == state_id) 
            return true;
    }
    return false;
}

string Automaton::return_transition (string current_state, char symbol) {
    for (int i = 0; i < this->transition_table.size(); i++) {
        if (transition_table[i].origen_id == current_state) {
            if (transition_table[i].destination_symbol == symbol)
                return transition_table[i].destination_id;
        }
    }
    return NULL;
}

bool Automaton::check_string (string str) {
    for (int i = 0; i < str.size(); i++) {
        current_state = return_transition (this->current_state, str[i]);
    }
    return is_final (current_state);
}