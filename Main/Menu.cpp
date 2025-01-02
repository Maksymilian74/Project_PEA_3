#include "Menu.h"
#include "../Structures/Matrix.h"
#include "../Utils/ReadFile.h"
#include "../Algorithms/Algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Konstruktor odpowiedzialny za inicjalizacje domyslnych wartosci zmiennych
Menu::Menu() {
    inputFile = "";
    displayMatrix = false;
    iterations = 0;
    runTS = 0;
    runSA = 0;
    outputFile = "";
    progress = false;
    showResults = 0;
    stop_criterion = 0;
    neighborhoodSelection = "none";
    temperatureFactor = 0;
    timer = 0;
}

// Glowna metoda odpowiedzialna za wykonanie programu na podstawie wczytanej konfiguracji
void Menu::run() {
    loadConfig("config.txt");  // Wczytanie konfiguracji z pliku config.txt

    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych

    Matrix* asymmetricMatrix = nullptr;  // Wskaznik do dynamicznie alokowanej macierzy asymetrycznej

        ReadFile fileReader;
        int fileMatrixSize;
        try {
            // Wczytywanie rozmiaru macierzy z pliku
            fileMatrixSize = fileReader.getMatrixSize(inputFile);
                asymmetricMatrix = new Matrix(fileMatrixSize);
                fileReader.loadDataAsymmetric(inputFile, *asymmetricMatrix); // Wczytanie danych do macierzy asymetrycznej
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
            return;
        }


    Algorithms algorithms;  // Tworzenie obiektu klasy z algorytmami

    timer = 0;
    for (int i = 0; i < iterations; i++) {

        // Wyswietlanie macierzy
        if (displayMatrix) {
                asymmetricMatrix->display();
        }
        vector<int> bestPath;
        int minCost = 0;

        // Uruchomienie wybranych algorytmow
        if (runTS) {
                start = high_resolution_clock::now();
                minCost = algorithms.AsymmetricTabuSearch(*asymmetricMatrix, bestPath);
                stop = high_resolution_clock::now();
            timer += duration_cast<duration<double, milli>>(stop - start).count();
        }

        if (runSA) {
                start = high_resolution_clock::now();
                minCost = algorithms.AsymmetricSimulatedAnnealing(*asymmetricMatrix, bestPath);
                stop = high_resolution_clock::now();
            timer += duration_cast<duration<double, milli>>(stop - start).count();
        }

        // Zapis pojedynczych wynikow do pliku CSV
        if (runTS) {
            saveResultsToCSV("TabuSearch",asymmetricMatrix->getSize(), duration_cast<duration<double, milli>>(stop - start).count());
        }

        if (runSA) {
            saveResultsToCSV("SimulatedAnnealing",asymmetricMatrix->getSize(), duration_cast<duration<double, milli>>(stop - start).count());
        }

        timer += duration_cast<duration<double, milli>>(stop - start).count();

        if (showResults) {
            // Wyswietlenie wynikow
            cout << "Minimalny koszt trasy: " << minCost << endl;
            cout << "Najlepsza trasa: ";
            for (int city: bestPath) {
                cout << city << " ";
            }
            cout << endl << endl << endl;
        }

        // Wyswietlenie wskaznika postepu
        if (progress) {
            int progress = ((i + 1) * 100) / iterations;  // Obliczenie procenta ukonczenia symulacji
            cout << "Postep: " << progress << "%" << endl;
        }
    }

    // Zapis wynikow do pliku CSV
    if (runTS) {
        saveResultsToCSV("TabuSearch",asymmetricMatrix->getSize(), timer / iterations);
    }

    if (runSA) {
        saveResultsToCSV("SimulatedAnnealing",asymmetricMatrix->getSize(), timer / iterations);
    }

    delete asymmetricMatrix;
}

// Metoda odpowiedzialna za wczytywanie konfiguracji z pliku konfiguracyjnego
void Menu::loadConfig(const string& configFile) {
    ifstream file(configFile);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku konfiguracyjnego: " << configFile << endl;
        return;
    }

    string line;
    int lineCount = 0;

    while (getline(file, line)) {
        // Pomijanie komentarzy i pustych linii
        if (line.empty() || line[0] == '#') {
            continue;
        }

        string value = extractValue(line);  // Wyciaganie wartosci po znaku "="

        // Przypisanie wartosci na podstawie numeru linii
        switch (lineCount) {
            case 0:
                inputFile = value;
                break;
            case 1:
                displayMatrix = (value == "1");
                break;
            case 2:
                iterations = stoi(value);
                break;
            case 3:
                runTS = (value == "1");
                break;
            case 4:
                runSA = (value == "1");
                break;
            case 5:
                outputFile = value;
                break;
            case 6:
                progress = (value == "1");
                break;
            case 7:
                showResults = (value == "1");
                break;
            case 8:
                stop_criterion = stoi(value);
                break;
            case 9:
                neighborhoodSelection = value;
                break;
            case 10:
                temperatureFactor = stoi(value);
                break;
        }
        lineCount++;
    }
    file.close();
}

// Pomocnicza metoda do wyciagania wartosci po znaku "="
string Menu::extractValue(const string& line) {
    size_t tmp = line.find("=");
    if (tmp != string::npos) {
        return line.substr(tmp + 1);
    }
    return "";
}

// Metoda odpowiedzialna za zapis wyników do pliku CSV
void Menu::saveResultsToCSV(const string& algorithm, int size, double time) {
    ofstream file(outputFile, ios::app);  // Otwieranie pliku w trybie dopisywania
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku wyjsciowego: " << outputFile << endl;
        return;
    }

    file << algorithm << "," << size << "," << time << "\n";

    file.close();
}
