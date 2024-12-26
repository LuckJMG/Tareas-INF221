#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int c, n;
	while (cin >> c >> n) {
		vector<pair<int, int>> items(n); // <value, weight>
		for (int i = 0; i < n; i++) {
			pair<int, int> item;
			cin >> item.first >> item.second;
			items[i] = item;
		}

		int optimalMatrix[n+1][c+1];
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= c; j++) {
				if (i == 0) {
					optimalMatrix[i][j] = 0;
					continue;
				}

				int opt1 = optimalMatrix[i-1][j];
				int opt2 = -1;
				if (j - items[i-1].second >= 0) 
					opt2 = optimalMatrix[i-1][j-items[i-1].second] + items[i-1].first;
				optimalMatrix[i][j] = max(opt1, opt2);
			}
		}

		int i = n;
		int j = c;
		vector<int> indexes;
		while (i > 0 && j > 0) {
			if (optimalMatrix[i][j] != optimalMatrix[i-1][j]) {
				indexes.push_back(i-1);
				j -= items[i-1].second;
			}

			i--;
		}

		cout << indexes.size() << endl;
		for (int index : indexes) {
			cout << index << " ";
		}
		cout << endl;
	}
}

