#include "nfa.h"

void nfa::initialize_nfa () {
	system ("clear");
	cout << "Amount of states:  ";
	cin >> states_amount;
	for (int i = 1; i < states_amount; i++) {
		states_NFA[i].no = i;
	}

	system ("clear");
	cout << "Initial state ID: ";
	cin >> state_initial;

	system ("clear");
	cout << "Amount of final states: ";
	cin >> states_final_amount;

	system ("clear");
	cout << "Enter the final state ID: " << endl;
	for(int i = 1; i <= states_final_amount; i++) {
		int new_final_state;
		cout << "Final state #" << i << " ";
		cin >> new_final_state;
		final_states.push_back(new_final_state);
    }

	system ("clear");
	cout << "Amount of symbols: ";
	cin >> symbols_amount;

	system ("clear");
	cout << "Enter the symbols: " << endl;
	for (int i = 1; i <= symbols_amount; i++) {
		char new_symbol;
		cout << "Symbol #" << i << " ";
		cin >> new_symbol;
		symbols.push_back(new_symbol);
	}
	symbols.push_back('e');

	system ("clear");
	cout << "Insert the transitions. \n\nIf you want to stop enter -1\n\n" << endl;
	cout << "State ID\t\tSymbol\t\t\tDestination" << endl;
	for (int i = 1; i <= states_amount; i++) {
		for (int j = 0; j <= symbols_amount; j++) {
			int k = 0;
			bool make = true;
			struct transition new_transition;
			
			new_transition.symbol = symbols[j];
			states_NFA[i].transition_table.push_back(new_transition);

			do {
				printf("%d\t\t\t%c\t\t\t", i, symbols[j]);
				cin >> states_NFA[i].transition_table[j].destination[k++];

				if (states_NFA[i].transition_table[j].destination[k-1] == -1) {
					k--; 
					make = false;
					break;
				}
			} while (make != false);

			states_NFA[i].transition_table[j].id = k;
		}
	}
}

void nfa::set_stackA (int state_id, int transition_id) {
	int i = 0;

	while (i < states_NFA[state_id].transition_table[transition_id].id) {
		insert_stackA (states_NFA[state_id].transition_table[transition_id].destination[i++]);
	}
}

void nfa::insert_stackA (int value) {
	stackA[++stackA_ptr] = value;
}

void nfa::insert_stackB (int value) {
	stackB[++stackB_ptr] = value;
}

void nfa::transfer_stack (int state_id) {
	char temp[STATE_AMOUNT+1] = " ";
	int k = 0;
	stackB_ptr = -1;

	strcpy (temp, states_DFA[state_id].states);
	while (temp[k] != '\0') {
		insert_stackB (temp[k] - '0');
		k++;
	}
}

bool nfa::search_stack (int stack[], int ptr, int s) {
	for(int i = 0; i <= ptr; i++) {
		if(s == stack[i])
			return true;
	}

	return false;
}

void nfa::bubble_sort (int stack[]) {
	int temp;

	for (int i = 0; i < stackB_ptr; i++) {
		for (int j = 0; j < (stackB_ptr-i); j++) {
			if (stack[j] > stack[j+1]) {
				temp = stack[j];
				stack[j] = stack[j+1];
				stack[j+1] = temp;
			}
		}
	}
}

void nfa::set_queue () {
	int i = 0;

	bubble_sort (stackB);
	for (i = 0; i <= stackB_ptr; i++) {
		DFA_Queue[i] = stackB[i] + '0';
	}

	DFA_Queue[i] = '\0';
}

void nfa::print_DFA () {
	system ("clear");
	cout << "\t\t Transition Table " << endl;
	cout << "States\tString\t Destination" << endl;

	for (int i = 0; i < (symbols.size() - 1); i++) {
		printf("\t\t%c", symbols[i]);
	}

	for(int i = 0; i < states_DFA_amount; i++) {
		if(states_DFA[i].is_final == true)
			printf("\n*%c",states_DFA[i].name);
		else	
			printf("\n%c",states_DFA[i].name);
			
		printf("\t%s",states_DFA[i].states);
		for (int j = 0; j < symbols_amount; j++) {
			printf("\t%c",states_DFA[i].destination[j]);
		}
	}
	printf("\n");
}

void nfa::epsilon_closure (int state_id) {
	int auxiliary = state_id, current_id = state_id;
	bool exist;

	while (stackA_ptr != -1) {
		current_id = stackA[stackA_ptr--];
		int id = 0;
		auxiliary = current_id;

		while (id <= states_NFA[current_id].transition_table[symbols_amount].id) {
			exist = search_stack (stackB, stackB_ptr, auxiliary);
			if(exist == false)
				insert_stackB (auxiliary);

			auxiliary = states_NFA[current_id].transition_table[symbols_amount].destination[id++];
			exist = search_stack (stackA, stackA_ptr, auxiliary);
			if(exist == false && id <= states_NFA[current_id].transition_table[symbols_amount].id)
				insert_stackA (auxiliary);
		}
	}
}

void nfa::to_DFA () {
	int aux_id, converted_id = 0;
	
	if (state_initial == -1) {
		cout << "There is no initial state set." << endl;
		return;
	} else {
		insert_stackA (state_initial);
		epsilon_closure (stackA[stackA_ptr]);
		set_queue ();
	}

	states_DFA[states_DFA_amount].name = 'A';
	states_DFA_amount++;
	strcpy(states_DFA[0].states, DFA_Queue);

	while (converted_id < states_DFA_amount) {	
		for (int j = 0; j < symbols_amount; j++) {
			bool is_final = false;

			transfer_stack (converted_id);
			while (stackB_ptr != -1) {
				set_stackA(stackB[stackB_ptr--], j);
			}

			while(stackA_ptr != -1)
				epsilon_closure (stackA[stackB_ptr]);

			set_queue ();
			for (aux_id = 0; aux_id < states_DFA_amount; aux_id++) {
				if ((strcmp(DFA_Queue, states_DFA[aux_id].states) == 0)) {
					states_DFA[converted_id].destination[j]=states_DFA[aux_id].name;
					break;
				}
			}

			if (aux_id == states_DFA_amount) {
				states_DFA_amount++;

				for (aux_id = 0; aux_id < states_final_amount; aux_id++) {
					is_final = search_stack (stackB, stackB_ptr, final_states[aux_id]);
					if (is_final == true) {
						states_DFA[states_DFA_amount-1].is_final = 1;
						break;
					}									
				}
				
				strcpy(states_DFA[states_DFA_amount-1].states, DFA_Queue);
				states_DFA[states_DFA_amount-1].name = 'A' + (states_DFA_amount-1);
				states_DFA[converted_id].destination[j] = states_DFA[states_DFA_amount-1].name;
			}
		}
		converted_id++;
	}
	print_DFA();
}

string nfa::to_string (const string &file_name) {
	ifstream file (file_name.c_str());

	if (!file.is_open())
		throw "Error opening file";

	string line;
	string evaluation = "";
	while (getline(file, line)) {
		evaluation = evaluation + line;
	}

	return evaluation;
}


/*
for(int i = 0; i < states_DFA_amount; i++) {
		if(states_DFA[i].is_final == true)
			printf("\n*%c",states_DFA[i].name);
		else	
			printf("\n%c",states_DFA[i].name);
			
		printf("\t%s",states_DFA[i].states);
		for (int j = 0; j < symbols_amount; j++) {
			printf("\t%c",states_DFA[i].destination[j]);
		}
	}
*/
nfa::state_DFA nfa::search_state (char name) {
	for (int i = 0; i < STATE_AMOUNT; i++) {
		if (states_DFA[i].name == name)
			return states_DFA[i];
	}
}

bool nfa::check_file (const string &file) {
	string file_name = "data/" + file + ".txt";
	struct state_DFA current_state = states_DFA[0];

	try {
		string evaluate = to_string (file_name);

		for (int i = 0; i < evaluate.size(); i++) {
			for (int j = 0; j < symbols_amount; j++) {
				if (evaluate[i] == symbols[j]) {
					current_state = search_state (current_state.destination[j]);
				}
			}
		}

		if (current_state.is_final)
			cout << "The file accomplish the requirements of the automaton." << endl;
		else 
			cout << "The file doesn't accomplish the requirements of the automaton." << endl;

	} catch (char const *error_message) {
		cout << error_message << endl;
	}
}

void nfa::execute () {
	initialize_nfa ();
	to_DFA ();
}