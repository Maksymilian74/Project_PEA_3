/*
 * Klasa Algorithms odpowiedzialna jest za implementacje
 * algorytmu rozwiazywania problemu komiwojazera oraz metody pomocniczej
 *
 */

#ifndef PROJEKT_PEA_2_ALGORITHMS_H
#define PROJEKT_PEA_2_ALGORITHMS_H

#include "../Structures/Matrix.h"
#include <vector>
#include <random>

using namespace std;

class Algorithms {
public:
    // Metoda Simulated Annealing
    int SimulatedAnnealing(const Matrix& matrix, vector<int>& bestPath, double initialTemperature, const string& neighborhoodSelection, double temperatureFactor, int stop_criterion);

private:
    // Metoda najbliższego sąsiada
    std::vector<int> nearestNeighbor(const Matrix& matrix) const;

    // Funkcja do obliczania kosztu ścieżki
    int calculateCost(const Matrix& matrix, const std::vector<int>& path) const;

    // Funkcja generowania sąsiada
    std::vector<int> generateNeighbor(const std::vector<int>& path, const std::string& neighborhoodSelection, std::mt19937& rng) const;

};

#endif
