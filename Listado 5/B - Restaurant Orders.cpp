#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int itemCount;
	cin >> itemCount;

	vector<long long int> menu(itemCount+1);
	for (int item = 1; item <= itemCount; item++) cin >> menu[item];

	long long int costs[itemCount+1][30001];
	for (int item = 0; item <= itemCount; item++) costs[item][0] = 1;
	for (int cost = 1; cost <= 30000; cost++) costs[0][cost] = 0;
	
	for (int item = 1; item <= itemCount; item++) {
		for (int cost = 0; cost <= 30000; cost++) {
			costs[item][cost] = costs[item-1][cost]; // Not add the item
			if (cost >= menu[item])
				costs[item][cost] += costs[item][cost - menu[item]];
		}
	}

	int orderCount;
	cin >> orderCount;
	for (int order = 0; order < orderCount; order++) {
		int price;
		cin >> price;

		if (costs[itemCount][price] == 0) {
			cout << "Impossible" << endl;
			continue;
		}
		if (costs[itemCount][price] > 1) {
			cout << "Ambiguous" << endl;
			continue;
		}

		vector<int> indexes;
		int item = itemCount;
		int cost = price;
		while (item > 0 && cost > 0) {
			int notAdd = costs[item-1][cost];
			int add = costs[item][cost - menu[item]];
			// cout << notAdd << " " << add << endl;

			if (notAdd == 1) {
				item--;
				continue;
			}

			cost -= menu[item];
			indexes.push_back(item);
		}

		sort(indexes.begin(), indexes.end());
		for (int index : indexes) {
			cout << index << " ";
		}
		cout << endl;
	}
}

