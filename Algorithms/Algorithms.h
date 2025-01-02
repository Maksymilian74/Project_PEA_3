/*
 * Klasa Algorithms odpowiedzialna jest za implementacje dwoch
 * algorytmow rozwiazywania problemu komiwojazera oraz metody pomocniczej
 *
 */

#ifndef PROJEKT_PEA_2_ALGORITHMS_H
#define PROJEKT_PEA_2_ALGORITHMS_H

#include "../Structures/Matrix.h"
#include <vector>

using namespace std;

class Algorithms {
public:
    // Metoda Tabu Search dla macierzy asymetrycznej
    int AsymmetricTabuSearch(const Matrix& matrix, vector<int>& bestPath);

    // Metoda Simulated Annealing dla macierzy asymetrycznej
    int AsymmetricSimulatedAnnealing(const Matrix& matrix, vector<int>& bestPath);
};


#endif
