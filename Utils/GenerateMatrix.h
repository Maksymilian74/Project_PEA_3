/*
 * Klasa GenerateMatrix odpowiedzialna jest za generowanie
 * losowych danych dla macierzy kosztow, wypelnia macierz
 * losowymi wartosciami z danego zakresu
 */

#ifndef PROJEKT_PEA_2_GENERATEMATRIX_H
#define PROJEKT_PEA_2_GENERATEMATRIX_H

#include "../Structures/Matrix.h"

class GenerateMatrix {
public:
    // Metoda generujaca losowe wartosci i wypelniająca macierz
    void fillRandomMatrix(Matrix& matrix);

};

#endif
