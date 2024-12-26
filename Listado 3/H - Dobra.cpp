#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;
typedef long long int ll;

string s;
vector<int> ways(101, 1);
ll ans = 0;

bool isvalid() {
	bool hasL = false, isVowel = true;
	int count = 0;
	for (char &c: s) {
		if (c == 'L') hasL = true;

		if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
			if (isVowel) count++;
			else {
				isVowel = true;
				count = 1;
			}
		} else {
			if (isVowel) {
				isVowel = false;
				count = 1;
			} else count++;
		}

		if (count >= 3) return false;
	}

	return hasL;
}

void solve(int i) {
	if (i == s.length()) {
		if (isvalid()) {
			ll count = 1;
			for (int j = 0; j < s.size(); j++) count *= ways[j];
			ans += count;
		}

		return;
	}

	if (s[i] != '_') solve(i + 1);
	else {
		// try L
		s[i] = 'L';
		solve(i + 1);

		// try consonant
		s[i] = 'B';
		ways[i] = 20;
		solve(i + 1);

		// try vowel
		s[i] = 'A';
		ways[i] = 5;
		solve(i + 1);

		s[i] = '_';
		ways[i] = 1;
	}
}

int main() {
	cin >> s;
	solve(0);
	cout << ans << endl;
	return 0;
}
