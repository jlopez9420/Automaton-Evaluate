#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> get_states ();
vector<char> get_symbols ();
string get_initial ();
vector<string> get_finals ();
vector<string> get_transitions (vector<string> states, vector<char> symbols);

#endif