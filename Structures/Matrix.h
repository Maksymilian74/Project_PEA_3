/*
 * Klasa Matrix odpowiedzialna jest za implementacje macierzy kosztow,
 * zapewnia mechanike ustawiania oraz pobierania kosztow,
 * a takze wyswietlania macierzy.
 */

#ifndef PROJEKT_PEA_2_MATRIX_H
#define PROJEKT_PEA_2_MATRIX_H

#include <iostream>
#include <iomanip>
#include <stdexcept>

class Matrix {
private:
    int size;        // Rozmiar macierzy
    int** matrix;    // Macierz kosztow

public:
    // Konstruktor
    Matrix(int n);

    // Destruktor
    ~Matrix();

    // Metoda odpowiedzialna za wyswietlenie macierzy
    void display() const;

    // Metoda odpowiedzialna za pobieranie wartosci z macierzy
    int getCost(int i, int j) const;

    // Metoda odpowiedzialna za ustawienie wartosci w macierzy
    void setCost(int i, int j, int cost);

    // Getter zwracajacy rozmiar macierzy
    int getSize() const;
};

#endif
