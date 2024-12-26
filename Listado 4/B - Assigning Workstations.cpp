#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
	int n, m;
	cin >> n >> m;

	vector<pair<int, int>> researchers(n);
	for (int i = 0; i < n; i++)
		cin >> researchers[i].first >> researchers[i].second;
	sort(researchers.begin(), researchers.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });

	int count = 0;
	priority_queue<int, vector<int>, greater<int>> activeWorkstations;
	for (pair<int, int> researcher : researchers) {
		int endTime = researcher.first + researcher.second;

		while (!activeWorkstations.empty() && activeWorkstations.top() + m < researcher.first) {
			activeWorkstations.pop();
		}

		if (!activeWorkstations.empty() && activeWorkstations.top() <= researcher.first) {
			count++;
			activeWorkstations.pop();
		}

		activeWorkstations.push(endTime);}

	cout << count << endl;
}

