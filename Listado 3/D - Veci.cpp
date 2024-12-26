#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	string num;
	getline(cin, num);

	vector<char> digits(num.size());
	for (int i = 0; i < num.size(); i++) digits[i] = num[i];
	if (next_permutation(digits.begin(), digits.end())) {
		for (char digit : digits) cout << digit;
		cout << endl;
	}
	else {
		cout << "0" << endl;
	}
}

