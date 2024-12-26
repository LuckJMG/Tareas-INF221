#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "costos.hpp"

using namespace std;

constexpr int letterCount = 26;
int cost_insert[letterCount];
int cost_delete[letterCount];
int cost_replace[letterCount][letterCount];
int cost_transpose[letterCount][letterCount];

// Helper function to read a line of integers
vector<int> parseLine(const string& line) {
    vector<int> result;
    istringstream stream(line);
    int value;
    while (stream >> value) result.push_back(value);
    return result;
}

void loadTables() {
	// Load cost_insert.txt
	ifstream insertFile("cost_insert.txt");
	if (insertFile.is_open()) {
		string line;
		if (getline(insertFile, line)) {
			auto values = parseLine(line);
			if (values.size() == letterCount)
				for (int i = 0; i < letterCount; ++i)
					cost_insert[i] = values[i];
			else
				cerr << "Error: cost_insert.txt should have exactly 26 values." << endl;
		}
		insertFile.close();
	} else
		cerr << "Error: Failed to open cost_insert.txt." << endl;

	// Load cost_delete.txt
	ifstream deleteFile("cost_delete.txt");
	if (deleteFile.is_open()) {
		string line;
		if (getline(deleteFile, line)) {
			auto values = parseLine(line);
			if (values.size() == letterCount)
				for (int i = 0; i < letterCount; ++i)
					cost_delete[i] = values[i];
			else cerr << "Error: cost_delete.txt should have exactly 26 values." << endl;
		}
		deleteFile.close();
	}
	else cerr << "Error: Failed to open cost_delete.txt." << endl;

	// Load cost_replace.txt
	ifstream replaceFile("cost_replace.txt");
	if (replaceFile.is_open()) {
		for (int i = 0; i < letterCount; ++i) {
			string line;
			if (getline(replaceFile, line)) {
				auto values = parseLine(line);
				if (values.size() == letterCount)
					for (int j = 0; j < letterCount; ++j)
						cost_replace[i][j] = values[j];
				else cerr << "Error: Each line in cost_replace.txt should have exactly 26 values." << endl;
			} else {
				cerr << "Error: Insufficient lines in cost_replace.txt." << endl;
				break;
			}
		}
		replaceFile.close();
	} else cerr << "Error: Failed to open cost_replace.txt." << endl;

	// Load cost_transpose.txt
	ifstream transposeFile("cost_transpose.txt");
	if (transposeFile.is_open()) {
		for (int i = 0; i < letterCount; ++i) {
			string line;
			if (getline(transposeFile, line)) {
				auto values = parseLine(line);
				if (values.size() == letterCount)
					for (int j = 0; j < letterCount; ++j)
						cost_transpose[i][j] = values[j];
				else cerr << "Error: Each line in cost_transpose.txt should have exactly 26 values." << endl;
			} else {
				cerr << "Error: Insufficient lines in cost_transpose.txt." << endl;
				break;
			}
		}
		transposeFile.close();
	}
	else cerr << "Error: Failed to open cost_transpose.txt." << endl;
}

// Calcula el costo de sustituir el carácter 'a' por 'b'.
// Parámetros:
// - a: carácter original
// - b: carácter con el que se sustituye
// Return: costo de sustituir 'a' por 'b'
int costo_sub(char a, char b) {
	return cost_replace[static_cast<int>(a) - 97][static_cast<int>(b) - 97];
}

// Calcula el costo de insertar el carácter 'b'.
// Parámetros:
// - b: carácter a insertar
// Return: costo de insertar 'b'
int costo_ins(char b) {
	return cost_insert[static_cast<int>(b) - 97];
}

// Calcula el costo de eliminar el carácter 'a'.
// Parámetros:
// - a: carácter a eliminar
// Return: costo de eliminar 'a'
int costo_del(char a) {
	return cost_delete[static_cast<int>(a) - 97];
}

// Calcula el costo de transponer el carácter 'a' por 'b'.
// Parámetros:
// - a: primer carácter a transponer
// - b: segundo carácter a transponer
// Return: costo de transponer 'a' y 'b'
int costo_trans(char a, char b) {
	return cost_transpose[static_cast<int>(a) - 97][static_cast<int>(b) - 97];
}

