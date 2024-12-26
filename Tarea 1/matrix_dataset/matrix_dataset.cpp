#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using matrix2d = vector<vector<int>>;

/*
 * Nombre: generateMatrix
 *
 * Descripción: Genera una matriz con las dimensiones especificadas que
 * contiene números al azar con un valor máximo de la multiplicación de
 * sus dimensiones.
 *
 * Parámetros:
 * - matrix2d& matrix, matriz que rellenar
 * - int rowCount, cantidad de filas
 * - int columnCount, cantidad de columnas
 */
void generateMatrix(matrix2d& matrix, int rowCount, int columnCount) {
	for (int i = 0; i < rowCount; i++) {
		// Generar columna con valores aleatorios
		vector<int> column(columnCount);
		generate(column.begin(), column.end(), rand);
		
		// Limitar valores a las dimensiones de la matriz
		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
			column[columnIndex] = column[columnIndex] % (columnCount * rowCount);
		}

		matrix.push_back(column);
	}
}

int main() {
	constexpr int minPower = 2;
	constexpr int maxPower = 10;
	constexpr int testCount = 10;

	ofstream datasetFile;
	datasetFile.open("matrix.txt");

	// Ingresar cantidad de potencias de 2 a testear y 
	// cantidad de test por potencia
	datasetFile << maxPower - minPower + 1 << endl;
	datasetFile << testCount << endl;

	// Generar matrices por cada potencia de 2 permitida
	for (int power = minPower; power <= maxPower; power++) {
		cout << "Generating matrix with 2^" << power << " rows test cases" << endl;
		int matrixDimension = pow(2, power); 
		datasetFile << matrixDimension << endl;

		// Generar testCount matrices de prueba
		for (int i = 0; i < testCount; i++) {
			matrix2d matrix;
			generateMatrix(matrix, matrixDimension, matrixDimension);
			
			for (int row = 0; row < matrixDimension; row++) {
				for (int column = 0; column < matrixDimension; column++) {
					datasetFile << matrix[row][column] << " ";
				}
			}
			datasetFile << endl;
		}
	}
	cout << "matrix.txt generated" << endl;

	datasetFile.close();
}
