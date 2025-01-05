#include "ReadFile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Metoda odpowiedzialna za wczytanie rozmiaru macierzy z pliku
int ReadFile::getMatrixSize(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;
        throw runtime_error("Blad: Nie mozna otworzyc pliku");
    }

    string line;
    while (getline(file, line)) {
        if (line.find("DIMENSION") != string::npos) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                return stoi(line.substr(pos + 1));
            }
        }
    }

    throw runtime_error("Blad: Nie znaleziono rozmiaru macierzy (DIMENSION) w pliku.");
}

// Metoda odpowiedzialna za wczytywanie danych z pliku
void ReadFile::loadData(const string& filename, Matrix& matrix) {
    ifstream file(filename);  // Otwarcie pliku do odczytu
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;  // Wyswietlenie bledu, jesli pliku nie mozna otworzyc
        throw runtime_error("Blad: Nie mozna otworzyc pliku");
    }

    string line;
    bool inEdgeWeightSection = false;
    int size = matrix.getSize();
    int i = 0, j = 0;

    while (getline(file, line)) {
        if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
            inEdgeWeightSection = true;
            continue;
        }

        if (inEdgeWeightSection) {
            istringstream lineStream(line);
            int cost;
            while (lineStream >> cost) {
                matrix.setCost(i, j, cost);
                j++;
                if (j == size) {  // Przejscie do kolejnego wiersza macierzy
                    i++;
                    j = 0;
                }
                if (i == size) break;  // Koniec wczytywania danych
            }
        }
    }

    if (i != size) {
        throw runtime_error("Blad: Nieprawidlowa liczba elementow w sekcji EDGE_WEIGHT_SECTION.");
    }
    file.close();
}
