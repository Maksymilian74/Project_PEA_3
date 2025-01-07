/*
 * Klasa Algorithms odpowiedzialna jest za implementacje
 * algorytmu rozwiazywania problemu komiwojazera oraz metod pomocniczych
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
    int SimulatedAnnealing(const Matrix& matrix, vector<int>& bestPath, double initialTemperature, const string& neighborhoodSelection, double temperatureFactor, int stop_criterion, double& bestPathTime, double& bestPathTemperature, const string& coolingMethod);

private:
    // Metoda najblizszego sasiada
    std::vector<int> nearestNeighbor(const Matrix& matrix) const;

    // Funkcja do obliczania kosztu sciezki
    int calculateCost(const Matrix& matrix, const std::vector<int>& path) const;

    // Funkcja generowania sasiada
    std::vector<int> generateNeighbor(const std::vector<int>& path, const std::string& neighborhoodSelection, std::mt19937& rng) const;

};

#endif
