/*
 * Klasa Algorithms odpowiedzialna jest za implementacje trzech
 * algorytmow rozwiazywania problemu komiwojazera oraz metody pomocniczej
 * do obliczania granicy
 */

#ifndef PROJEKT_PEA_2_ALGORITHMS_H
#define PROJEKT_PEA_2_ALGORITHMS_H

#include "../Structures/Matrix.h"
#include "../Structures/SymmetricMatrix.h"
#include "../Structures/Node.h"
#include "../Structures/Stack.h"
#include "../Structures/Queue.h"
#include <vector>

using namespace std;

class Algorithms {
public:
    // Metoda branch and bound BFS dla macierzy asymetrycznej
    int AsymmetricBranchAndBoundBFS(const Matrix& matrix, vector<int>& bestPath);
};


#endif
