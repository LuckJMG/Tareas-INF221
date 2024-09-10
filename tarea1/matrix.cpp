#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;
using matrix2d = vector<vector<int>>;

// Funciones auxiliares

/*
 * Nombre: createMatrix
 *
 * Descripción: Crea una matríz de 2 dimensiones compuesta de solo 0
 *
 * Parámetros:
 * - int N, cantidad de columnas y filas que tendrá la matriz
 *
 * Returns: matrix2d, nueva matriz generada con 0
 */
matrix2d createMatrix(int N) {
	matrix2d newMatrix(N);
	for (int i = 0; i < N; i++) {
		vector<int> row(N, 0);
		newMatrix[i] = row;
	}
	return newMatrix;
}

/*
 * Nombre: add
 *
 * Descripción: suma 2 matrices
 *
 * Parámetros:
 * - matrix2d A, primera matriz sumando
 * - matrix2d B, segunda matriz sumando
 *
 * Returns: matrix2d, suma de las matrices A y B
 */
matrix2d add(matrix2d A, matrix2d B) {
	int N = A.size();
	matrix2d C = createMatrix(N);

	for (unsigned int i = 0; i < N; i++)
		for (unsigned int j = 0; j < N; j++)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

/*
 * Nombre: substract
 *
 * Descripción: resta 2 matrices
 *
 * Parámetros:
 * - matrix2d A, matriz a la que restarle
 * - matrix2d B, matriz que resta
 *
 * Returns: matrix2d, resta de las matrices A con B
 */
matrix2d subtract(matrix2d A, matrix2d B) {
	int N = A.size();
	matrix2d C = createMatrix(N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

// Algoritmos de multiplicación
/*
 * Nombre: cubicMultiplication
 *
 * Descripción: multiplica 2 matrices ocupando el algoritmo cúbico de
 * multiplicación de matrices. Implementación personal del pseudocódigo
 * descrito en https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Iterative_algorithm.
 *
 * Parámetros:
 * - matrix2d& A, primera matriz que multiplicar
 * - matrix2d& B, segunda matriz que multiplicar
 * - matrix2d& out, matriz resultante de la multiplicación
 */
void cubicMultiplication(matrix2d& A, matrix2d& B, matrix2d& out) {
	int rowCount = A.size();
	int columnCount = B[0].size();
	int dimension = A[0].size();

	for (int row = 0; row < rowCount; row++) {
		for (int column = 0; column < columnCount; column++) {
			int sum = 0;
			for (int index = 0; index < dimension; index++) {
				sum += A[row][index] * B[index][column];
			}

			out[row][column] = sum;
		}
	}
}

/*
 * Nombre: optimizedCubicMultiplication
 *
 * Descripción: multiplica 2 matrices ocupando el algoritmo cúbico de
 * multiplicación de matrices, pero aprovechandose del uso del cache
 * transponiendo la segunda matriz. Implementación personal del pseudocódigo
 * descrito en https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Iterative_algorithm.
 *
 * Parámetros:
 * - matrix2d& A, primera matriz que multiplicar
 * - matrix2d& B, segunda matriz que multiplicar
 * - matrix2d& out, matriz resultante de la multiplicación
 */
void optimizedCubicMultiplication(matrix2d& A, matrix2d& B, matrix2d& out) {
	// Transponer matriz para optimizar el uso de caché
	int rowCount = B.size();
	int columnCount = B[0].size();
	for (int row = 0; row < rowCount; row++) {
		for (int column = row + 1; column < columnCount; column++) {
			int tmp = B[row][column];
			B[row][column] = B[column][row];
			B[column][row] = tmp;
		}
	}

	// Multiplicación de matrices
	rowCount = A.size();
	columnCount = B[0].size();
	int dimension = A[0].size();
	for (int row = 0; row < rowCount; row++) {
		for (int column = 0; column < columnCount; column++) {
			int sum = 0;
			for (int index = 0; index < dimension; index++) {
				sum += A[row][index] * B[column][index];
			}

			out[row][column] = sum;
		}
	}
}

/*
 * Nombre: strassenMultiplication
 *
 * Descripción: Multiplica 2 matrices ocupando el algoritmo de Strassen,
 * que funciona mediante recursión y la táctica de dividir y conquistar.
 * Código módificado de https://github.com/psakoglou/Strassen-Algorithm-Simulation-and-Asymptotic-Efficiency-CPP
 *
 * Parámetros:
 * - matrix2d A, primera matriz que multiplicar
 * - matrix2d B, segunda matriz que multiplicar
 *
 * Returns: matrix2d, matriz resultante de la multiplicación
 */
matrix2d strassenMultiplication(matrix2d A, matrix2d B) {
	int N = A.size();
	if (N == 1) {
		matrix2d C = createMatrix(N);
		cubicMultiplication(A, B, C);
		return C;
	}

	matrix2d C = createMatrix(N);
	int K = N / 2;

	matrix2d A11 = createMatrix(K);
	matrix2d A12 = createMatrix(K);
	matrix2d A21 = createMatrix(K);
	matrix2d A22 = createMatrix(K);
	matrix2d B11 = createMatrix(K);
	matrix2d B12 = createMatrix(K);
	matrix2d B21 = createMatrix(K);
	matrix2d B22 = createMatrix(K);

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][K + j];
			A21[i][j] = A[K + i][j];
			A22[i][j] = A[K + i][K + j];
			B11[i][j] = B[i][j];
			B12[i][j] = B[i][K + j];
			B21[i][j] = B[K + i][j];
			B22[i][j] = B[K + i][K + j];
		}
	}

	matrix2d S1 = subtract(B12, B22);
	matrix2d S2 = add(A11, A12);
	matrix2d S3 = add(A21, A22);
	matrix2d S4 = subtract(B21, B11);
	matrix2d S5 = add(A11, A22);
	matrix2d S6 = add(B11, B22);
	matrix2d S7 = subtract(A12, A22);
	matrix2d S8 = add(B21, B22);
	matrix2d S9 = subtract(A11, A21);
	matrix2d S10 = add(B11, B12);

	matrix2d P1 = strassenMultiplication(A11, S1);
	matrix2d P2 = strassenMultiplication(S2, B22);
	matrix2d P3 = strassenMultiplication(S3, B11);
	matrix2d P4 = strassenMultiplication(A22, S4);
	matrix2d P5 = strassenMultiplication(S5, S6);
	matrix2d P6 = strassenMultiplication(S7, S8);
	matrix2d P7 = strassenMultiplication(S9, S10);

	matrix2d C11 = subtract(add(add(P5, P4), P6), P2);
	matrix2d C12 = add(P1, P2);
	matrix2d C21 = add(P3, P4);
	matrix2d C22 = subtract(subtract(add(P5, P1), P3), P7);

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			C[i][j] = C11[i][j];
			C[i][j + K] = C12[i][j];
			C[K + i][j] = C21[i][j];
			C[K + i][K + j] = C22[i][j];
		}
	}

	return C;
}

int main() {
	// Elección de algoritmo a testear
	int algorithmSelection;
	cout << "1) CubicMultiplication" << endl;
	cout << "2) OptimizedCubicMultiplication" << endl;
	cout << "3) StrassenMultiplication" << endl;
	cout << "Select algorithm to test: ";
	cin >> algorithmSelection;
	cout << endl;

	string multiplicationFunctionName;
	void (*multiplicationFunction)(matrix2d&, matrix2d&, matrix2d&);
	switch (algorithmSelection) {
		case 1:
			multiplicationFunctionName = "CubicMultiplication";
			multiplicationFunction = cubicMultiplication;
			break;
		case 2:
			multiplicationFunctionName = "OptimizedCubicMultiplication";
			multiplicationFunction = optimizedCubicMultiplication;
			break;
		default:
			multiplicationFunctionName = "StrassenMultiplication";
			multiplicationFunction = [](matrix2d& matrixA, matrix2d& matrixB, matrix2d& outMatrix) {
				matrixB = strassenMultiplication(matrixA, matrixB);
			};
			break;
	}

	// Testear algortimo seleccionado con dataset seleccionado
	cout << "Testing " << multiplicationFunctionName << endl;
	ifstream dataFile;
	dataFile.open("matrix_dataset/matrix.txt");

	int dataSizeCount;
	dataFile >> dataSizeCount;

	int testCount;
	dataFile >> testCount;

	int dimension;
	for (; dataSizeCount > 0; dataSizeCount--) {
		// Extraer tamaño de los vectores a testear del dataset
		dataFile >> dimension;
		vector<int> testDurations;

		for (int testIndex = testCount; testIndex > 0; testIndex -= 2) {
			// Extraer vector de testeo del dataset
			matrix2d matrixA = createMatrix(dimension);
			for (int row = 0; row < dimension; row++) {
				for (int column = 0; column < dimension; column++) {
					dataFile >> matrixA[row][column];
				}
			}

			matrix2d matrixB = createMatrix(dimension);
			for (int row = 0; row < dimension; row++) {
				for (int column = 0; column < dimension; column++) {
					dataFile >> matrixB[row][column];
				}
			}

			matrix2d outMatrix = createMatrix(dimension);

			// Multiplicar matrices y calcular tiempo
			auto start = chrono::high_resolution_clock::now();
			multiplicationFunction(matrixA, matrixB, outMatrix);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			testDurations.push_back(duration.count());
		}

		// Mostrar resultados
		cout << multiplicationFunctionName << " | ";
		cout << "Data Size: " << dimension << " | ";
		cout << "Duration: " << accumulate(testDurations.begin(), testDurations.end(), 0) / testCount << " μs" << endl;
	}

	cout << "Finished testing " << multiplicationFunctionName << endl;
	dataFile.close();
}
