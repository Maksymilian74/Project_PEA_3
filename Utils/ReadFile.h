/*
 * Klasa ReadFile odpowiedzialna jest za wczytywanie danych
 * z pliku tekstowego do macierzy, zapisuje dane
 * do odpowiednich komorek macierzy.
 */

#ifndef PROJEKT_PEA_2_READFILE_H
#define PROJEKT_PEA_2_READFILE_H

#include <string>
#include "../Structures/Matrix.h"
#include "../Structures/SymmetricMatrix.h"

using namespace std;

class ReadFile {
public:
    // Metoda odpowiedzialna za wczytanie rozmiaru macierzy z pliku
    int getMatrixSize(const string& filename);

    // Metoda odpowiedzialna za wczytywanie danych z pliku do macierzy asymetrzycznej
    void loadDataAsymmetric(const string& filename, Matrix& matrix);

    // Metoda odpowiedzialna za wczytywanie danych z pliku do macierzy symetrzycznej
    void loadDataSymmetric(const std::string& filename, SymmetricMatrix& matrix);
};

#endif
