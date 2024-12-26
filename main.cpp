#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main() {
	ll k, n;
	cin >> k >> n;

	ll minCount = (n + 2) / 3;
	ll maxCount = (n + 1) / 2;

	if (k < minCount || k > maxCount) {
		cout << "*" << endl;
		return 0;
	}

	ll count3 = 2 * (maxCount - k);
	ll count2 = k - count3;

	string result = "";
	for (int i = 0; i < count2; i++) {
		result += "X-";
	}
	for (int i = 0; i < count3; i++) {
		result += "-X-";
	}

	int extra = result.size() - n;
	if (extra == 2) {
		result = result.substr(0, result.size()-2);
	}
	if (extra == 1) {
		result = result.substr(0, result.size()-1);
	}

	cout << result << endl;
}
