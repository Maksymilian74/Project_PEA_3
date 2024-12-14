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
    bool generateData;   // Zmienna przechowujaca informacje czy generowac dane losowe
    string inputFile;  // Zmienna przechowujaca nazwe pliku wejsciowego
    bool symmetricProblem; // Czy problem jest symetryczny
    int instanceSize;  // Zmienna przechowujaca rozmiar instancji macierzy
    bool displayMatrix;   // Zmienna przechowujaca informacje czy wyswietlac macierz
    int iterations;  // Zmienna przechowujaca liczbe iteracji
    string algorithm;  // Zmienna przechowujaca nazwe wybranego algorytmu do uruchomienia
    string outputFile;  // Zmienna przechowujaca nazwe pliku wyjsciowego
    bool progress;  // Zmienna przechowujaca informacje czy wyswietlac pasek postepu
    bool showResults;  // Zmienna przechowujaca informacje czy wyswietlac wyniki dzialania algorytmu
    high_resolution_clock::time_point start, stop;  // Zmienne do przechowywania punktow czasowych do mierzenia czasu wykonania
    double timer;  // Zmienna przechowujaca zmierzony czas wykonania algorytmu

    string extractValue(const string& line); // Pomocnicza metoda do wyciagania wartosci po "="
    void saveResultsToCSV(const string& algorithm, int size, double time);  // Pomocnicza metoda odpowiedzialna za zapis pomiarow do pliku
};

#endif

