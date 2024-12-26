#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> t(n);
	for (int i = 0; i < n; i++) cin >> t[i];
	sort(t.begin(), t.end());

	vector<int> l(m);
	for (int i = 0; i < m; i++) cin >> l[i];
	sort(l.begin(), l.end());

	int count = 0;
	for (int i = 0, j = 0; i < n && j < m;) {
		if (t[i] > l[j]) {
			j++;
			continue;
		}

		count++;
		i++;
		j++;
	}

	cout << count << endl;
}

