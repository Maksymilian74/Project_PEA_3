#include "Matrix.h"

using namespace std;

// Konstruktor
Matrix::Matrix(int n) : size(n) {
    // Alokacja pamieci dla macierzy
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = -1; // Domyslna wartosc dla macierzy kosztow
        }
    }
}

// Destruktor
Matrix::~Matrix() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Metoda odpowiedzialna za wyswietlenie macierzy
void Matrix::display() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == -1) {
                cout << " -1 ";
            } else {
                cout << setw(3) << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Metoda odpowiedzialna za pobieranie wartosci z macierzy
int Matrix::getCost(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw out_of_range("Indeks poza zakresem macierzy");
    }
    return matrix[i][j];
}

// Metoda odpowiedzialna za ustawienie wartosci w macierzy
void Matrix::setCost(int i, int j, int cost) {
    if (i < 0 || i >= size || j < 0 || j >= size) {
        throw out_of_range("Indeks poza zakresem macierzy");
    }
    matrix[i][j] = cost;
}

// Getter zwracajacy rozmiar macierzy
int Matrix::getSize() const {
    return size;
}
