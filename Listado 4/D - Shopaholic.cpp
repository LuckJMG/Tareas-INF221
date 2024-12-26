#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	sort(p.begin(), p.end());

	long long int max_discount = 0;
	for (int i = n - 3; i >= 0; i -= 3) {
		max_discount += p[i];
	}

	cout << max_discount << endl;
}

