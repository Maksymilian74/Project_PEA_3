#include "GenerateMatrix.h"
#include <cstdlib>

using namespace std;

// Metoda odpowiedzialna za generowanie losowych wartosci dla macierzy kosztow
void GenerateMatrix::fillRandomMatrix(Matrix &matrix) {
    int size = matrix.getSize();
    const int maxCost = 100;  // Stala wartosc maksymalnego kosztu

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                matrix.setCost(i, j, -1);  //  Ustawienie -1 na przekatnej
            } else {
                int cost = rand() % maxCost + 1;  // Losowanie wartosci z zakresu [1, maxCost]
                matrix.setCost(i, j, cost);
            }
        }
    }
}

