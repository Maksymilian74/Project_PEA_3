#include "Menu.h"
#include "../Structures/Matrix.h"
#include "../Structures/SymmetricMatrix.h"
#include "../Utils/ReadFile.h"
#include "../Utils/GenerateMatrix.h"
#include "../Algorithms/Algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Konstruktor odpowiedzialny za inicjalizacje domyslnych wartosci zmiennych
Menu::Menu() {
    generateData = false;
    inputFile = "";
    symmetricProblem = 0;
    instanceSize = 0;
    displayMatrix = false;
    iterations = 0;
    algorithm = "";
    outputFile = "";
    progress = false;
    showResults = 0;
    timer = 0;
}

// Glowna metoda odpowiedzialna za wykonanie programu na podstawie wczytanej konfiguracji
void Menu::run() {
    loadConfig("config.txt");  // Wczytanie konfiguracji z pliku config.txt

    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych

    Matrix* asymmetricMatrix = nullptr;  // Wskaznik do dynamicznie alokowanej macierzy asymetrycznej
    SymmetricMatrix* symmetricMatrix = nullptr; // Wskaznik do dynamicznie alokowanej macierzy symetrycznej

    if (!generateData) {
        ReadFile fileReader;
        int fileMatrixSize;
        try {
            // Wczytywanie rozmiaru macierzy z pliku
            fileMatrixSize = fileReader.getMatrixSize(inputFile);
            if (symmetricProblem) {
                symmetricMatrix = new SymmetricMatrix(fileMatrixSize);
                fileReader.loadDataSymmetric(inputFile, *symmetricMatrix); // Wczytanie danych do macierzy symetrycznej
            } else {
                asymmetricMatrix = new Matrix(fileMatrixSize);
                fileReader.loadDataAsymmetric(inputFile, *asymmetricMatrix); // Wczytanie danych do macierzy asymetrycznej
            }
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
            return;
        }
    }  else {
        // Tworzenie macierzy na podstawie rozmiaru z konfiguracji
        if (symmetricProblem) {
            symmetricMatrix = new SymmetricMatrix(instanceSize);
        } else {
            asymmetricMatrix = new Matrix(instanceSize);
        }
    }

    GenerateMatrix generator;  // Tworzenie obiektu generatora losowych danych

    Algorithms algorithms;  // Tworzenie obiektu klasy z algorytmami

    timer = 0;
    for (int i = 0; i < iterations; i++) {

        // Wypelnienie macierzy losowymi danymi dla kazdej iteracji
        if (generateData) {
            if (symmetricProblem) {
                generator.fillRandomSymmetricMatrix(*symmetricMatrix);
            } else {
                generator.fillRandomAsymmetricMatrix(*asymmetricMatrix);
            }
        }

        // Wyswietlanie macierzy
        if (displayMatrix) {
            if (symmetricProblem) {
                symmetricMatrix->display();
            } else {
                asymmetricMatrix->display();
            }
        }
        vector<int> bestPath;
        int minCost = 0;

        // Uruchomienie wybranego algorytmu
        if (!symmetricProblem) { // Algorytmy dla problemu asymetrycznego
            if (algorithm == "BranchAndBoundBFS") {
                start = high_resolution_clock::now();
                minCost = algorithms.AsymmetricBranchAndBoundBFS(*asymmetricMatrix, bestPath);
                stop = high_resolution_clock::now();

            } else if (algorithm == "BranchAndBoundDFS") {
                start = high_resolution_clock::now();
                minCost = algorithms.AsymmetricBranchAndBoundDFS(*asymmetricMatrix, bestPath);
                stop = high_resolution_clock::now();

            } else if (algorithm == "BranchAndBoundBestFirstSearch") {
                start = high_resolution_clock::now();
                minCost = algorithms.AsymmetricBranchAndBoundBestFirstSearch(*asymmetricMatrix, bestPath);
                stop = high_resolution_clock::now();
            } else {
                cerr << "Blad: Nieznany algorytm dla problemu asymetrycznego!" << endl;
                return;
            }
        } else { // Algorytmy dla problemu symetrycznego
            if (algorithm == "BranchAndBoundBFS") {
                start = high_resolution_clock::now();
                minCost = algorithms.SymmetricBranchAndBoundBFS(*symmetricMatrix, bestPath);
                stop = high_resolution_clock::now();

            } else if (algorithm == "BranchAndBoundDFS") {
                start = high_resolution_clock::now();
                minCost = algorithms.SymmetricBranchAndBoundDFS(*symmetricMatrix, bestPath);
                stop = high_resolution_clock::now();

            } else if (algorithm == "BranchAndBoundBestFirstSearch") {
                start = high_resolution_clock::now();
                minCost = algorithms.SymmetricBranchAndBoundBestFirstSearch(*symmetricMatrix, bestPath);
                stop = high_resolution_clock::now();
            } else {
                cerr << "Blad: Nieznany algorytm dla problemu symetrycznego!" << endl;
                return;
            }
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
    if (symmetricProblem) {
        saveResultsToCSV(algorithm + "_Symmetric", symmetricMatrix->getSize(), timer / iterations);
    } else {
        saveResultsToCSV(algorithm + "_Asymmetric", asymmetricMatrix->getSize(), timer / iterations);
    }

    cout << endl << "Algorytm " << algorithm;

    if (symmetricProblem) {
        cout << " dla problemu symetrycznego";
        cout << ", dla macierzy o rozmiarze: " << symmetricMatrix->getSize();
    } else {
        cout << " dla problemu asymetrycznego";
        cout << ", dla macierzy o rozmiarze: " << asymmetricMatrix->getSize();
    }
    cout << ", sredni czas: " << timer / iterations << " ms" << endl;

    delete asymmetricMatrix;
    delete symmetricMatrix;
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
                generateData = (value == "1");
                break;
            case 1:
                inputFile = value;
                break;
            case 2:
                if (!value.empty()) {
                    symmetricProblem = (value == "1");
                }
                break;
            case 3:
                if (!value.empty()) {
                    instanceSize = stoi(value);
                }
                break;
            case 4:
                displayMatrix = (value == "1");
                break;
            case 5:
                iterations = stoi(value);
                break;
                break;
            case 6:
                algorithm = value;
                break;
            case 7:
                outputFile = value;
                break;
            case 8:
                progress = (value == "1");
                break;
            case 9:
                showResults = (value == "1");
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
