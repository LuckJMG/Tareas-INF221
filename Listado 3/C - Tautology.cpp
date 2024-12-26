#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

// Define the logical operations
bool K(bool w, bool x) { return w && x; } // AND
bool A(bool w, bool x) { return w || x; } // OR
bool N(bool w) { return !w; }              // NOT
bool C(bool w, bool x) { return !w || x; } // IMPLIES
bool E(bool w, bool x) { return w == x; }  // EQUIVALENT

// Evaluate the WFF for given values of p, q, r, s, t
bool evaluateWFF(const string &wff, const unordered_map<char, bool> &variables) {
	stack<bool> stk;

	for (auto it = wff.rbegin(); it != wff.rend(); ++it) {
		char ch = *it;
		if (ch == 'p' || ch == 'q' || ch == 'r' || ch == 's' || ch == 't') {
			stk.push(variables.at(ch));
		} else if (ch == 'N') {
			bool w = stk.top(); stk.pop();
			stk.push(N(w));
		} else if (ch == 'K' || ch == 'A' || ch == 'C' || ch == 'E') {
			bool x = stk.top(); stk.pop();
			bool w = stk.top(); stk.pop();
			if (ch == 'K') stk.push(K(w, x));
			else if (ch == 'A') stk.push(A(w, x));
			else if (ch == 'C') stk.push(C(w, x));
			else if (ch == 'E') stk.push(E(w, x));
		}
	}

	return stk.top(); // The result of the evaluation
}

bool isTautology(const string &wff) {
	// Test all combinations of truth values for p, q, r, s, t
	for (int i = 0; i < 32; i++) { // 2^5 = 32 combinations
		unordered_map<char, bool> variables;
		variables['p'] = (i & 16) != 0; // p = 1 if bit 4 is set
		variables['q'] = (i & 8) != 0;  // q = 1 if bit 3 is set
		variables['r'] = (i & 4) != 0;  // r = 1 if bit 2 is set
		variables['s'] = (i & 2) != 0;  // s = 1 if bit 1 is set
		variables['t'] = (i & 1) != 0;  // t = 1 if bit 0 is set

		// Evaluate the WFF for the current combination
		if (!evaluateWFF(wff, variables)) {
			return false; // Found a combination where it is not true
		}
	}
	return true; // All combinations resulted in true
}

int main() {
	string wff;

	while (true) {
		getline(cin, wff);
		if (wff == "0") break; // End of input

		if (isTautology(wff)) {
			cout << "tautology" << endl;
		} else {
			cout << "not" << endl;
		}
	}

	return 0;
}

