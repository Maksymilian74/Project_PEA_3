#ifndef PROJEKT_PEA_2_SYMMETRICMATRIX_H
#define PROJEKT_PEA_2_SYMMETRICMATRIX_H

#include <stdexcept>

class SymmetricMatrix {
private:
    int size;      // Liczba wierzcholkow
    int* costs;    // Jednowymiarowa dynamiczna tablica przechowujaca koszty

    int getIndex(int i, int j) const; // Wyliczanie indeksu w tablicy

public:
    SymmetricMatrix(int size);  // Konstruktor
    ~SymmetricMatrix();  // Destruktor

    void setCost(int i, int j, int value); // Ustawia koszt krawedzi
    int getCost(int i, int j) const;       // Zwraca koszt krawedzi
    void display() const;                  // Metoda do wyswietlania macierzy
    int getSize() const;                   // Zwraca rozmiar macierzy
};

#endif
