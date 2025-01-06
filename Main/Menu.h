/*
 * Klasa Menu odpowiedzialna jest za zarzadzanie glowna logika programu.
 * Odpowiada za wczytywanie konfiguracji z pliku, tworzenie macierzy,
 * wybieranie i uruchamianie odpowiedniego algorytmu oraz za mierzenie czasu
 */

#ifndef PROJEKT_PEA_2_MENU_H
#define PROJEKT_PEA_2_MENU_H

#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Menu {
public:
    Menu();  // Konstruktor
    void run();  // Glowna metoda uruchamiajaca dzialanie programu
    void loadConfig(const string& configFile);  // Metoda odpowiedzialna za wczytanie danych z pliku konfiguracyjnego

private:
    string inputFile;  // Zmienna przechowujaca nazwe pliku wejsciowego
    bool displayMatrix;   // Zmienna przechowujaca informacje czy wyswietlac macierz
    int iterations;  // Zmienna przechowujaca liczbe iteracji
    bool runSA;  // Zmienna przechowujaca informacje czy wywolywac algorytm Simulated Annealing
    string outputFile;  // Zmienna przechowujaca nazwe pliku wyjsciowego
    bool progress;  // Zmienna przechowujaca informacje czy wyswietlac pasek postepu
    bool showResults;  // Zmienna przechowujaca informacje czy wyswietlac wyniki dzialania algorytmu
    int stop_criterion; // Zmienna przechowujaca informacje o kryterium stopu
    string neighborhoodSelection; // Zmienna przechowujaca informacje o wyborze sasiedztwa
    int initialTemperature; // Zmienna przechowujaca informacje o temperaturze poczatkowej
    double temperatureFactor; // Zmienna przechowujaca informacje o wspolczynniku zmiany temperatury
    high_resolution_clock::time_point start, stop;  // Zmienne do przechowywania punktow czasowych do mierzenia czasu wykonania
    double timer;  // Zmienna przechowujaca zmierzony czas wykonania algorytmu

    string extractValue(const string& line); // Pomocnicza metoda do wyciagania wartosci po "="
    void saveResultsToCSV(const string& algorithm, int size, int cost, double time, double temperature);  // Pomocnicza metoda odpowiedzialna za zapis pomiarow do pliku
};

#endif

