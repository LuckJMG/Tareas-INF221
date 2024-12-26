#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int l, d, n;
	cin >> l >> d >> n;

	if (n == 0) {
		cout << (((l - 6) - 6) / d) + 1 << endl;
		return 0;
	}

	vector<int> birds(n);
	for (int i = 0; i < n; i++) {
		cin >> birds[i];
	}

	sort(birds.begin(), birds.end());

	int birdCount = (birds[0] - 6) / d;
	for (int i = 0; i < n-1; i++) {
		birdCount += (birds[i+1] - birds[i]) / d - 1;
	}
	birdCount += (l - 6 - birds[n-1]) / d;

	cout << birdCount << endl;
}

