#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakończone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    // Sprawdzenie poprawności rozmiarów macierzy
    if (mat->r != mat->c || mat->r != b->r || x->r != b->r || x->c != 1 || b->c != 1) {
        return 2; // Błąd nieprawidłowych rozmiarów macierzy
    }

    int n = mat->r; // Liczba równań
    // Inicjalizacja wyniku (macierz x)
    for (int i = 0; i < n; i++) {
        x->data[i][0] = 0.0;
    }

    // Wsteczne podstawianie
    for (int i = n - 1; i >= 0; i--) {
        if (mat->data[i][i] == 0.0) {
            return 1; // Błąd dzielenia przez 0
        }
        // Obliczanie wartości niewiadomej
        x->data[i][0] = b->data[i][0];
        for (int j = i + 1; j < n; j++) {
            x->data[i][0] -= mat->data[i][j] * x->data[j][0];
        }
        x->data[i][0] /= mat->data[i][i];
    }

    return 0; // Sukces
}
