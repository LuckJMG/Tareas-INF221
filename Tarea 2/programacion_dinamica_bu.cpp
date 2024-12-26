#include <climits>
#include <iostream>
#include <string>
#include <algorithm>
#include "costos.hpp"

using namespace std;

int main() {
	string original, destino;
	cin >> original >> destino;

	int n = original.size();
	int m = destino.size();
	int costMatrix[n + 1][m + 1];

	// Caso ambas cadenas de caracteres vacias
	costMatrix[0][0] = 0;

	// Casos cadena destino vacia
	for (int i = 0; i <= n; i++) {
		costMatrix[i][0] = 0;
		for (int k = 0; k < i; k++)
			costMatrix[i][0] += costo_del(original[k]);
	}

	// Casos cadena original vacia
	for (int j = 0; j <= m; j++) {
		costMatrix[0][j] = 0;
		for (int k = 0; k < j; k++)
			costMatrix[0][j] += costo_ins(destino[k]);
	}

	// Rellenar matriz de costos
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int costoInsertar = costo_ins(destino[j-1]) + costMatrix[i][j-1];
			int costoEliminar = costo_del(original[i-1]) + costMatrix[i-1][j];
			int costoReemplazar = costo_sub(original[i-1], destino[j-1]) + costMatrix[i-1][j-1];
			int costoTransponer = INT_MAX;
			if (i >= 2 && j >= 2 && original[i-1] == destino[j-2] && original[i-2] == destino[j-1])
				costoTransponer = costo_trans(original[i-2], original[i-1]) + costMatrix[i-2][j-2];

			costMatrix[i][j] = min({ costoInsertar, costoEliminar, costoReemplazar, costoTransponer });
		}
	}

	cout << "  | ";
	for (int j = 0; j <= m; j++) {
		cout << j << " ";
	}
	cout << endl;

	cout << "--+-";
	for (int j = 0; j <= m; j++) {
		cout << "--";
	}
	cout << endl;

	for (int i = 0; i <= n; i++) {
		cout << i << " | ";
		for (int j = 0; j <= m; j++) {
			cout << costMatrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << costMatrix[n][m] << endl;
}
