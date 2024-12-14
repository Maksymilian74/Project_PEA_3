#include "ReadFile.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Metoda odpowiedzialna za wczytanie rozmiaru macierzy z pliku
int ReadFile::getMatrixSize(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;
        throw runtime_error("Blad: Nie mozna otworzyc pliku");
    }

    int size;
    file >> size;  // Odczyt rozmiaru macierzy z pierwszej linii pliku
    file.close();

    return size;
}

// Metoda odpowiedzialna za wczytywanie danych z pliku
void ReadFile::loadDataAsymmetric(const string& filename, Matrix& matrix) {
    ifstream file(filename);  // Otwarcie pliku do odczytu
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;  // Wyswietlenie bledu, jesli pliku nie mozna otworzyc
        throw runtime_error("Blad: Nie mozna otworzyc pliku");
    }

    int size;
    file >> size;  // Wczytanie rozmiaru macierzy z pliku

    // Wczytanie danych z pliku do macierzy
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int cost;
            file >> cost;  // Wczytanie kosztu z pliku
            matrix.setCost(i, j, cost);  // Ustawienie kosztu w macierzy
        }
    }

    file.close();  // Zamkniecie pliku po wczytaniu danych
}

// Metoda odpowiedzialna za wczytywanie danych z pliku dla problemu symetrycznego
void ReadFile::loadDataSymmetric(const string& filename, SymmetricMatrix& matrix) {
    ifstream file(filename);  // Otwarcie pliku do odczytu
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku: " << filename << endl;
        throw runtime_error("Blad: Nie mozna otworzyc pliku");
    }

    int size;
    file >> size;  // Wczytanie rozmiaru macierzy z pliku

    if (size != matrix.getSize()) {
        cerr << "Blad: Rozmiar macierzy w pliku nie zgadza sie z rozmiarem struktury danych." << endl;
        throw runtime_error("Rozmiar macierzy niezgodny");
    }

    // Wczytanie danych z pliku i ustawienie tylko dolnej polowy macierzy
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int cost;
            file >> cost;  // Wczytanie kosztu z pliku
            if (i > j) {  // Ustawiamy tylko dla dolnej polowy macierzy
                matrix.setCost(i, j, cost);
            }
        }
    }

    file.close();  // Zamkniecie pliku po wczytaniu danych
}
