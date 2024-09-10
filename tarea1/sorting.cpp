#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

/*
 * Nombre: bubbleSort
 *
 * Descripción: Función para sortear un vector de enteros ocupando el 
 * algortimo bubble sort. Modificación del código presentado en
 * https://www.geeksforgeeks.org/bubble-sort-in-cpp/
 *
 * Parámetros:
 * - vector<int>& dataVector, referencia al vector de enteros a ordenar
 */
void bubbleSort(vector<int>& dataVector) {
	int length = dataVector.size();

	for (int top = length; top > 0; top--) {
		for (int index = 0; index < top - 1; index++) {
			if (dataVector[index] <= dataVector[index + 1]) continue;

			int tmp = dataVector[index];
			dataVector[index] = dataVector[index + 1];
			dataVector[index + 1] = tmp;
		}
	}
}

/*
 * Nombre: mergeSort
 *
 * Descripción: Función para sortear un vector de enteros ocupando el 
 * algortimo merge sort. Modificación del código presentado en
 * https://www.geeksforgeeks.org/cpp-program-for-merge-sort/
 *
 * Parámetros:
 * - vector<int>& dataVector, referencia al vector de enteros a ordenar
 * - int bottom, indice limite inferior
 * - int top, indice limite superior
 */
void mergeSort(vector<int>& dataVector, int bottom, int top) {
	if (bottom >= top) return;

	int middle = int((top - bottom) / 2) + bottom;

	mergeSort(dataVector, bottom, middle);
	mergeSort(dataVector, middle + 1, top);

	int leftIndex = bottom;
	int rightIndex = middle + 1;
    int i = 0;

	int range = top - bottom + 1;
	vector<int> tmp(range);

	// Fusionar vectores una vez estos están ordenados
	while (leftIndex <= middle && rightIndex <= top) {
		if (dataVector[leftIndex] <= dataVector[rightIndex]) {
			tmp[i++] = dataVector[leftIndex++];
		} else {
			tmp[i++] = dataVector[rightIndex++];
		}
	}

	while (leftIndex <= middle) {
		tmp[i++] = dataVector[leftIndex++];
	}

	while (rightIndex <= top) {
		tmp[i++] = dataVector[rightIndex++];
	}

	for (int j = 0; j < range; j++) {
		dataVector[bottom + j] = tmp[j];
	}
}

/*
 * Nombre: quickSort
 *
 * Descripción: Función para sortear un vector de enteros ocupando el 
 * algortimo quick sort. Modificación del código presentado en
 * https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 *
 * Parámetros:
 * - vector<int>& dataVector, referencia al vector de enteros a ordenar
 * - int bottom, indice limite inferior
 * - int top, indice limite superior
 */
void quickSort(vector<int>& vec, int bottom, int top) {
    if (bottom >= top) return;

	int pivot = vec[top];
	int i = bottom - 1;

	for (int j = bottom; j <= top - 1; j++) {
		if (vec[j] <= pivot) {
			i++;
			int tmp = vec[i];
			vec[i] = vec[j];
			vec[j] = tmp;
		}
	}

	int p = i + 1;
	int tmp = vec[p];
	vec[p] = vec[top];
	vec[top] = tmp;

	quickSort(vec, bottom, p - 1);
	quickSort(vec, p + 1, top);
}

/*
 * Nombre: testSortingFunction
 *
 * Descripción: Función para testear funciones de sorteo en un cierto
 * dataset con distintos tamaños, imprime un promedio de cuanto tarda en
 * sortear un vector del dataset de los tamaños especificados
 *
 * Parámetros:
 * - string datasetName, nombre del dataset
 * - string datasetFileName, nombre del archivo del dataset
 * - string sortingFunctionName, nombre de la función a ocupar
 * - void (*sortingFunction)(vector<int>&), puntero a función de sorteo
 *   que recibe una referencia a un vector de enteros
 */
void testSortingFunction(string datasetName, string datasetFileName, string sortingFunctionName, void (*sortingFunction)(vector<int>&)) {
	cout << "Testing " << sortingFunctionName << " with " << datasetName << " dataset" << endl;
	ifstream dataFile;
	dataFile.open(datasetFileName);

	int dataSizeCount;
	dataFile >> dataSizeCount;

	int testCount;
	dataFile >> testCount;

	int dataSize;
	for (; dataSizeCount > 0; dataSizeCount--) {
		// Extraer tamaño de los vectores a testear del dataset
		dataFile >> dataSize;
		vector<int> testDurations;

		for (int testIndex = testCount; testIndex > 0; testIndex--) {
			// Extraer vector de testeo del dataset
			vector<int> testVector(dataSize);
			for (int index = 0; index < dataSize; index++) {
				dataFile >> testVector[index];
			}

			// Sortear vector y calcular tiempo
			auto start = chrono::high_resolution_clock::now();
			sortingFunction(testVector);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			testDurations.push_back(duration.count());
		}

		// Mostrar resultados
		cout << sortingFunctionName << " | ";
		cout << datasetName << " | ";
		cout << "Data Size: " << dataSize << " | ";
		cout << "Duration: " << accumulate(testDurations.begin(), testDurations.end(), 0) / testCount << " μs" << endl;
	}

	cout << "Finished testing " << sortingFunctionName << " with " << datasetName << " dataset" << endl;
	dataFile.close();
}

int main() {
	// Elección de algoritmo a testear
	int algorithmSelection;
	cout << "1) BubbleSort" << endl;
	cout << "2) MergeSort" << endl;
	cout << "3) QuickSort" << endl;
	cout << "4) std::sort (C++)" << endl;
	cout << "Select algorithm to test: ";
	cin >> algorithmSelection;
	cout << endl;

	string sortingFunctionName;
	void (*sortingFunction)(vector<int>&);
	switch (algorithmSelection) {
		case 1:
			sortingFunctionName = "BubbleSort";
			sortingFunction = bubbleSort;
			break;
		case 2:
			sortingFunctionName = "MergeSort";
			sortingFunction = [](vector<int>& testVector) {
				mergeSort(testVector, 0, testVector.size() - 1);
			};
			break;
		case 3:
			sortingFunctionName = "QuickSort";
			sortingFunction = [](vector<int>& testVector) {
				quickSort(testVector, 0, testVector.size() - 1);
			};
			break;
		default:
			sortingFunctionName = "std::sort (C++)";
			sortingFunction = [](vector<int>& testVector) {
				sort(testVector.begin(), testVector.end());
			};
			break;
	}

	// Elección de dataset con el que testear
	int datasetSelection;
	cout << "1) Random" << endl;
	cout << "2) Partially Sorted" << endl;
	cout << "3) Sorted" << endl;
	cout << "4) Reverse Sorted" << endl;
	cout << "Select dataset to test with: ";
	cin >> datasetSelection;
	cout << endl;

	string datasetFileName;
	string datasetName;
	switch (datasetSelection) {
		case 1:
			datasetName = "random";
			datasetFileName = "sorting_dataset/random.txt";
			break;
		case 2:
			datasetName = "partially sorted";
			datasetFileName = "sorting_dataset/partially_sorted.txt";
			break;
		case 3:
			datasetName = "sorted";
			datasetFileName = "sorting_dataset/sorted.txt";
			break;
		default:
			datasetName = "reverse sorted";
			datasetFileName = "sorting_dataset/reverse_sorted.txt";
			break;
	}

	// Testear algortimo seleccionado con dataset seleccionado
	testSortingFunction(datasetName, datasetFileName, sortingFunctionName, sortingFunction);
}
