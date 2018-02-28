#include "Menu.h"

/* *
 * We ask for the amount of states and they will be initialized by default
 * with letter 'S'. For example S1->S2->S3->S4. Finally it returns a vector
 * with all the states ID.
 * */
vector<string> get_states () {
    vector<string> states;
    int n;

    system ("clear");

    cout << "Welcome! We will start by setting up your automaton.\n" << endl;
    cout << "How many states do you want?" << endl;
    cin >> n;    
    for (int i = 1; i <= n; i++) {
        ostringstream ss; 
        ss << i;
        string str =  "S" + ss.str();
        states.push_back (str);
    }

    return states;
}
/* *
 * We ask for the amount of symbols and they will be initialized by user.
 * It will return a vector with all the symbols entered by the user. 
 * */
vector<char> get_symbols () {
    vector<char> symbols;
    int n;
    char s;
    
    system ("clear");

    cout << "How many symbols do you want?" << endl;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Enter symbol #" << i << ": ";
        cin >> s;
        symbols.push_back (s);
    }

    return symbols;
}
/* *
 * We ask for the ID number of the initial state, convert it to
 * string and return it.
 * */
string get_initial () {
    ostringstream ss;
    int initial;

    system ("clear");

    cout << "Enter the number of the initial state: ";
    cin >> initial;

    ss << initial;
    string str =  "S" + ss.str();

    return str;
}

/* *
 * We ask for the amount of final states and they will be initialized by
 * user. It will return a vector with the final states entered by the user.
 * */
vector<string> get_finals () {
    vector<string> finals;
    ostringstream ss;
    string str;
    int n;
    int x;

    system ("clear"); 
    
    cout << "How many final states do you want?" << endl;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Enter final state ID #" << i << ": ";
        cin >> x;
        ss << x;
        str =  "S" + ss.str();
        finals.push_back (str);
    }

    return finals;
}

/* *
 * We ask for the destination by creating the transitions table, once we complete
 * all the transitions we return a vector with all the destinations.
 * */          
vector<string> get_transitions (vector<string> states, vector<char> symbols) {
    vector<string> transitions;
    int x;

    system("clear");

    cout << "Origin - Symbol - Destination" << endl;
    for (int i = 0; i < states.size(); i++) {
        for (int j = 0; j < symbols.size(); j++) {
            cout << states[i] << "       " << symbols[j] << "        ";
            string str;
            cin >> str;
            transitions.push_back (str);
        }
    }

    return transitions;
}