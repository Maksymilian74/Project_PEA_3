#include "SymmetricMatrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Konstruktor inicjalizujacy rozmiar macierzy i alokujacy pamiec
SymmetricMatrix::SymmetricMatrix(int size) : size(size) {
    if (size <= 0) {
        throw invalid_argument("Rozmiar macierzy musi byc wiekszy od zera.");
    }

    // Alokacja pamieci dla jednowymiarowej tablicy
    costs = new int[size * (size - 1) / 2];

    // Inicjalizacja kosztow na -1
    for (int i = 0; i < size * (size - 1) / 2; i++) {
        costs[i] = -1;
    }
}

// Destruktor zwalniajacy pamiec
SymmetricMatrix::~SymmetricMatrix() {
    delete[] costs;
}

// Metoda obliczajaca indeks w tablicy jednowymiarowej
int SymmetricMatrix::getIndex(int i, int j) const {
    if (i < j) {
        swap(i, j);
    }
    return i * (i - 1) / 2 + j;
}

// Metoda ustawiajaca koszt krawedzi
void SymmetricMatrix::setCost(int i, int j, int value) {
    if (i == j) {
        throw invalid_argument("Nie mozna ustawic kosztu dla tego samego wierzcholka.");
    }
    if (i >= size || j >= size || i < 0 || j < 0) {
        throw out_of_range("Indeksy wierzcholkow sa poza zakresem.");
    }
    costs[getIndex(i, j)] = value;
}

// Metoda wyswietlajaca tablice
void SymmetricMatrix::display() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                cout << setw(5) << -1;
            } else {
                cout << setw(5) << getCost(i, j);
            }
        }
        cout << endl;
    }
}

// Metoda zwracajaca koszt krawedzi
int SymmetricMatrix::getCost(int i, int j) const {
    if (i == j) {
        return 0; // Koszt od wierzcholka do samego siebie
    }
    if (i >= size || j >= size || i < 0 || j < 0) {
        throw out_of_range("Indeksy wierzcholkow sa poza zakresem.");
    }
    return costs[getIndex(i, j)];
}

// Metoda zwracajaca rozmiar macierzy
int SymmetricMatrix::getSize() const {
    return size;
}

