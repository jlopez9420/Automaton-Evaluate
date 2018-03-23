#ifndef NFA_NFA_H
#define NFA_NFA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>

#define STATE_AMOUNT 50
#define STACK_AMOUNT 100

using namespace std;

class nfa {
    public:
        int stackA[STACK_AMOUNT], stackB[STACK_AMOUNT];
        int stackA_ptr = -1, stackB_ptr = -1;
        int state_initial;

        int states_amount, symbols_amount, states_final_amount, states_DFA_amount = 0;
        vector<char> symbols;
        char DFA_Queue[STATE_AMOUNT+1];

        vector<int> final_states;

        struct state_DFA {
            char name;
            char states[STATE_AMOUNT+1];
            char destination[10];
            bool is_final;
        }states_DFA[STATE_AMOUNT];

        struct transition {
            char symbol;
            int destination[50];
            int id;
        };

        struct state_NFA {
            int no;
            vector<transition> transition_table;
        }states_NFA[STATE_AMOUNT];

        void initialize_nfa ();
        void set_stackA (int state_id, int transition_id);
        void insert_stackA (int value);
        void insert_stackB (int value);
        void transfer_stack (int state_id);
        bool search_stack (int stack[], int ptr, int s);
        void bubble_sort (int stack[]);
        void set_queue ();
        void print_DFA ();
        void epsilon_closure (int state_id);
        void to_DFA ();
        bool check_file (const string &name);
        string to_string (const string &file_name);
        state_DFA search_state (char name);
        void execute (const string &file);
};
#endif