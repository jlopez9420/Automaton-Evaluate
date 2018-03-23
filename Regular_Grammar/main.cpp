#include <iostream>
#include <vector>

using namespace std;

struct transition {
    char state_name;
    vector<char> symbols;
    vector<char> destinations;
    bool is_terminal;
};

struct state {
    char state_name;
    vector<transition> transitions;
};

int main () {
	
    cout << "Hello Grammar!" << endl;

    cout << "Insert state name followed by symbol." << endl;
	return 0;
}