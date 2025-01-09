#include "Algorithms.h"
#include <cmath>
#include <random>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Metoda Simulated Annealing
int Algorithms::SimulatedAnnealing(const Matrix& matrix, vector<int>& bestPath, double initialTemperature, const string& neighborhoodSelection, double temperatureFactor, int stop_criterion, double& bestPathTime, const string& coolingMethod, double& finalTemperature) {
    vector<int> currentPath = nearestNeighbor(matrix);
    bestPath = currentPath;

    // Obliczenie kosztu dla pierwszej sciezki
    int bestCost = calculateCost(matrix, bestPath);
    int currentCost = bestCost;

    random_device rd;
    mt19937 rng(rd());

    double temperature = initialTemperature;
    int counter = 0;

    auto startTime = high_resolution_clock::now();

    while (true) {
        auto currentTime = high_resolution_clock::now();
        auto elapsedSeconds = duration_cast<milliseconds>(currentTime - startTime).count();
        if (elapsedSeconds >= stop_criterion) {
            break;
        }

        // Generowanie nowego sasiada
        vector<int> newPath = generateNeighbor(currentPath, neighborhoodSelection, rng);
        int newCost = calculateCost(matrix, newPath);

        int deltaCost = newCost - currentCost;
        if (deltaCost < 0) {
            currentPath = newPath;
            currentCost = newCost;
            counter = 0;

            if (currentCost < bestCost) {
                bestPath = currentPath;
                bestCost = currentCost;
                bestPathTime = elapsedSeconds;
            }
        }
        // Sprawdzenie, czy akceptujemy gorsze rozwiazanie zgodnie z prawdopodobienstwem
        else if (exp(-deltaCost / temperature) > uniform_real_distribution<>(0.0, 1.0)(rng)) {
            currentPath = newPath;
            currentCost = newCost;
            counter = 0;
        } else {
            counter++;
        }

        if (counter > 1000) {
            for (int i = 0; i < 10; i++) {
                currentPath = generateNeighbor(currentPath, "swap", rng);
            }
            currentCost = calculateCost(matrix, currentPath);
            counter = 0;
        }

        // Schladzanie temperatury
        if (coolingMethod == "geometric") {
            temperature *= temperatureFactor;
        } else if (coolingMethod == "logarithmic") {
            temperature = temperature / (1 + 0,001 * log(1 + temperature));
        } else {
            throw invalid_argument("Unknown cooling method: " + coolingMethod);
        }
    }

    finalTemperature = temperature;

    return bestCost;
}

// Metoda najblizszego sasiada
vector<int> Algorithms::nearestNeighbor(const Matrix& matrix) const {
    int n = matrix.getSize();
    vector<int> path;
    vector<bool> visited(n, false);

    // Start z pierwszego miasta
    int currentCity = 0;
    path.push_back(currentCity);
    visited[currentCity] = true;

    for (int i = 1; i < n; i++) {
        int nearestCity = -1;
        int minCost = numeric_limits<int>::max();

        // Znajdz najblizsze nieodwiedzone miasto
        for (int i = 0; i < n; i++) {
            if (!visited[i] && matrix.getCost(currentCity, i) < minCost) {
                nearestCity = i;
                minCost = matrix.getCost(currentCity, i);
            }
        }

        // Dodaj najblizsze miasto do sciezki
        if (nearestCity != -1) {
            currentCity = nearestCity;
            path.push_back(currentCity);
            visited[currentCity] = true;
        }
    }

    return path;
}

// Funkcja do obliczania kosztu sciezki
int Algorithms::calculateCost(const Matrix& matrix, const vector<int>& path) const {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += matrix.getCost(path[i], path[i + 1]);
    }
    cost += matrix.getCost(path.back(), path.front());  // Powrot do punktu poczatkowego
    return cost;
}

// Funkcja generowania sasiada
    vector<int> Algorithms::generateNeighbor(const vector<int>& path, const string& neighborhoodSelection, mt19937& rng) const {
    vector<int> neighbor = path;
    uniform_int_distribution<int> dist(0, path.size() - 1);

    if (neighborhoodSelection == "swap") {
        // Zamiana dwoch losowych miast
        int i = dist(rng), j = dist(rng);
        while (i == j) j = dist(rng);
        swap(neighbor[i], neighbor[j]);
    } else if (neighborhoodSelection == "invert") {
        // Odwrocenie losowego fragmentu sciezki
        int i = dist(rng), j = dist(rng);
        if (i > j) swap(i, j);
        while (i < j) {
            swap(neighbor[i], neighbor[j]);
            i++;
            j--;
        }
    } else if (neighborhoodSelection == "insert") {
        // Wybor miasta do przesuniecia
        int i = dist(rng);
        int city = neighbor[i]; // Wybrane miasto

        // Usuniecie miasta z obecnej pozycji
        neighbor.erase(neighbor.begin() + i);

        // Wybor nowej pozycji do wstawienia
        int j = dist(rng) % neighbor.size();
        neighbor.insert(neighbor.begin() + j, city);
    }
    return neighbor;
}
