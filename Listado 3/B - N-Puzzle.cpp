#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

string solution = "ABCDEFGHIJKLMNO.";

int main() {
	string puzzle = "";
	for (int i = 0; i < 4; i++) {
		string row;
		getline(cin, row);
		puzzle.append(row);
	}

	int scatter = 0;
	for (int solutionPos = 0; solutionPos < 15; solutionPos++) {
		auto it = find(puzzle.begin(), puzzle.end(), solution[solutionPos]);
		int pos = it - puzzle.begin();
		int rowDist = abs((solutionPos % 4) - (pos % 4));
		int columnDist = abs((solutionPos / 4) - (pos / 4));
		scatter += columnDist + rowDist;
	}

	cout << scatter << endl;
}

