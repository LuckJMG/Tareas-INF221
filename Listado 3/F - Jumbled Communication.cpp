#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
	int n;
	cin >> n;
	cin.ignore();

	string rawBytes;
	getline(cin, rawBytes);

	vector<int> bytes;
	string tmp = "";
	for (char c : rawBytes) {
		if (c == ' ') {
			bytes.push_back(stoi(tmp));
			tmp = "";
			continue;
		}

		tmp += c;
	}
	bytes.push_back(stoi(tmp));

	for (int byte : bytes) {
		int unscrambled_byte = 0;
		for (int i = 0; i < 256; i++) {
			if (byte == (i ^ (i << 1) & 0xFF)) {
				unscrambled_byte = i;
				break;
			}
		}
		cout << unscrambled_byte << " ";
	}
	cout << endl;
}

