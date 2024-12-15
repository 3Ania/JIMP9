#include "gauss.h"
#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int i, j, k;
    double factor;

    if (mat->r != mat->c || mat->r != b->r || b->c != 1) { // Sprawdza, czy macierz ma odpowiednie wymiary (jest kwadratowa + tablica wyników jest ok)
        fprintf(stderr, "Nieprawidlowe wymiary macierzy! %d x %d, %d, %d\n", mat->r, mat->c, b->r, b->c);
        return 1;
    }

    for (i = 0; i < mat->r - 1; i++) {
        if (mat->data[i][i] == 0.0) {
            fprintf(stderr, "Macierz osobliwa - dzielenie przez 0!\n");
            return 1;
        }

        for (j = i + 1; j < mat->r; j++) {
            factor = mat->data[j][i] / mat->data[i][i];
            for (k = 0; k < mat->c; k++) {
                mat->data[j][k] -= mat->data[i][k] * factor;
            }
            b->data[j][0] -= b->data[i][0] * factor;
        }
    }

    return 0;
}
