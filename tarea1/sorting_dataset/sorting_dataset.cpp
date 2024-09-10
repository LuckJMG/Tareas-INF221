#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

/*
 * Nombre: datasetGenerator
 *
 * Descripción: Genera un archivo .txt con vectores generados con la función
 * especificada. Esta estructurado de la siguiente forma, la primera linea
 * es n tamaños de vectores a testear, la segunda linea es k de vectores
 * por tamaño de vector, luego siguen n sectores que en su primera linea
 * se encuentra el tamaño del vector y k lineas con los vectores.
 *
 * Parámetros:
 * - string name, nombre del dataset a generar
 * - int minPower, potencia minima de 10 a generar
 * - int maxPower, potenica máxima de 10 a generar
 * - int testCount, cantidad de vectores por potencia a generar
 * - void (*generatorFunction)(vector<int>&), función generador de vectores
 *   que se ocupará para generar los vectores de testeo, recibe una
 *   referencia a un vector de enteros
 */
void datasetGenerator(string name, int minPower, int maxPower, int testCount, void (*generatorFunction)(vector<int>&)) {
	cout << "Generating " + name + ".txt" << endl;

	ofstream datasetFile;
	datasetFile.open(name + ".txt");

	// Ingresar cantidad de potencias de 10 a testear y 
	// cantidad de test por potencia
	datasetFile << maxPower - minPower + 1 << endl;
	datasetFile << testCount << endl;

	// Generar vectores por cada potencia de 10 permitida
	for (int power = minPower; power <= maxPower; power++) {
		cout << "Generating 10^" << power << " test cases" << endl;
		int vectorSize = pow(10, power); 
		datasetFile << vectorSize << endl;

		// Generar testCount vectores de prueba con la función dada
		for (int i = 0; i < testCount; i++) {
			vector<int> testVector(vectorSize);
			generatorFunction(testVector);
			
			for (int value : testVector) {
				datasetFile << value % vectorSize << " ";
			}
			datasetFile << endl;
		}
	}
	cout << name << ".txt generated" << endl;

	datasetFile.close();
}

int main() {
	srand(unsigned(time(nullptr)));

	constexpr int testCount = 10;
	constexpr int minPower = 2;
	constexpr int maxPower = 7;

	// Generar dataset random
	datasetGenerator("random", minPower, maxPower, testCount, 
			[](vector<int>& testVector) {
				generate(testVector.begin(), testVector.end(), rand);
			});

	// Generar dataset parcialmente ordenado
	datasetGenerator("partially_sorted", minPower, maxPower, testCount,
			[](vector<int>& testVector) {
				generate(testVector.begin(), testVector.end(), rand);
				sort(testVector.begin(), testVector.end());
			});

	// Generar dataset ordenado
	datasetGenerator("sorted", minPower, maxPower, testCount,
			[](vector<int>& testVector) {
				int vectorSize = testVector.size();
				generate(testVector.begin(), testVector.end(), rand);
				for (int i = 0; i < vectorSize; i++) {
					testVector[i] = testVector[i] % vectorSize;
				}

				sort(testVector.begin(), testVector.end());
			});

	// Generar dataset ordenado invertido
	datasetGenerator("reverse_sorted", minPower, maxPower, testCount,
			[](vector<int>& testVector) {
				int vectorSize = testVector.size();
				generate(testVector.begin(), testVector.end(), rand);
				for (int i = 0; i < vectorSize; i++) {
					testVector[i] = testVector[i] % vectorSize;
				}

				sort(testVector.begin(), testVector.end());
				reverse(testVector.begin(), testVector.end());
			});
}
