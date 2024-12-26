#include <climits>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <vector>
#include "costos.hpp"

using namespace std;
using namespace chrono;

constexpr int TEST_COUNT = 3;

int distanciaDeEdicion(string& original, string& destino, int n, int m) {
	if (n == 0) {
		int sum = 0;
		for (int i = 0; i < m; i++) sum += costo_ins(destino[i]);
		return sum;
	}
	
	if (m == 0) {
		int sum = 0;
		for (int i = 0; i < n; i++) sum += costo_del(original[i]);
		return sum;
	}

	if (original[n-1] == destino[m-1])
		return distanciaDeEdicion(original, destino, n-1, m-1);

	int costoInsertar = costo_ins(destino[m-1]) + distanciaDeEdicion(original, destino, n, m-1);
	int costoEliminar = costo_ins(original[n-1]) + distanciaDeEdicion(original, destino, n-1, m);
	int costoReemplazar = costo_sub(original[n-1], destino[m-1]) + distanciaDeEdicion(original, destino, n-1, m-1);
	int costoTransponer = INT_MAX;
	if (n >= 2 && m >= 2 && original[n-1] == destino[m-2] && original[n-2] == destino[m-1])
		costoTransponer = costo_trans(original[n-1], destino[m-1]) + distanciaDeEdicion(original, destino, n-2, m-2);

	return min({ costoInsertar, costoEliminar, costoReemplazar, costoTransponer });
}

int main() {
	loadTables();

	string datasetName;
	cin >> datasetName;

	ifstream dataset(datasetName);
	string datasetCase;
	int testIndex = 0;
	while (getline(dataset, datasetCase)) {
		testIndex++;
		int pos = datasetCase.find(' ');
		string original = datasetCase.substr(0, pos);
		string destino = datasetCase.substr(pos+1, datasetCase.size() - 1);
		// cout << "Length: " << pos << " | " << original << " " << destino << endl;
		
		vector<long long int> times(TEST_COUNT + 1);
		int result = 0;
		for (int i = 0; i <= TEST_COUNT; i++) {
			auto start = high_resolution_clock::now();
			result = distanciaDeEdicion(original, destino, original.size(), destino.size());
			auto end = high_resolution_clock::now();
			times[i] = duration_cast<nanoseconds>(end - start).count();
		}

		long long int average = 0;
		for (int i = 1; i <= TEST_COUNT; i++) average += times[i];
		average = average / TEST_COUNT;

		// cout << "Minimum Cost: " << result << endl; 
		// cout << "Time: " << average << " ns" << endl << endl;
		cout << testIndex << "," << result << "," << datasetName.substr(0, datasetName.size() - 4) << ",brute force," << average << endl;
	}
}
