#include "nfa.h"

int main () {
	nfa eval = nfa ();
	eval.execute ("text");

	return 0;
}