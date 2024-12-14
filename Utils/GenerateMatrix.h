/*
 * Klasa GenerateMatrix odpowiedzialna jest za generowanie
 * losowych danych dla macierzy kosztow, wypelnia macierz
 * losowymi wartosciami z danego zakresu
 */

#ifndef PROJEKT_PEA_2_GENERATEMATRIX_H
#define PROJEKT_PEA_2_GENERATEMATRIX_H

#include "../Structures/Matrix.h"
#include "../Structures/SymmetricMatrix.h"

class GenerateMatrix {
public:
    // Metoda generujaca losowe wartosci i wypelniająca asymetryczna macierz
    void fillRandomAsymmetricMatrix(Matrix& matrix);

    // Metoda generujaca losowe wartosci i wypelniająca symetryczna macierz
    void fillRandomSymmetricMatrix(SymmetricMatrix &matrix);
};

#endif
