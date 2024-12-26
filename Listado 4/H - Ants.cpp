#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int testCount;
	cin >> testCount;

	while (testCount > 0) {
		int l, n;
		cin >> l >> n;

		int mid = l / 2;

		vector<int> largestDistances(n);
		vector<int> shortestDistances(n);
		for (int i = 0; i < n; i++) {
			int distance;
			cin >> distance;

			if (distance < mid) {
				largestDistances[i] = l - distance;
				shortestDistances[i] = distance;
			}
			else {
				largestDistances[i] = distance;
				shortestDistances[i] = l - distance;
			}
		}

		sort(largestDistances.begin(), largestDistances.end());
		sort(shortestDistances.begin(), shortestDistances.end());

		cout << shortestDistances[shortestDistances.size() - 1] << " " << largestDistances[largestDistances.size() - 1] << endl;

		testCount--;
	}
}

