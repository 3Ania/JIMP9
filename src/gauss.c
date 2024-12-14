#include "gauss.h"
#include <stdio.h>
#include <math.h>

void swap_rows(Matrix *mat, Matrix *b, int row1, int row2) {
    double temp;
    int j;

    
    for (j = 0; j < mat->c; j++) {
        temp = mat->data[row1][j];
        mat->data[row1][j] = mat->data[row2][j];
        mat->data[row2][j] = temp;
    }

    
    temp = b->data[row1][0];
    b->data[row1][0] = b->data[row2][0];
    b->data[row2][0] = temp;
}

int find_max_in_col(Matrix *mat, int col, int start) {
    int max_row = start;
    double max_value = fabs(mat->data[start][col]);

    for (int i = start + 1; i < mat->r; i++) {
        if (fabs(mat->data[i][col]) > max_value) {
            max_value = fabs(mat->data[i][col]);
            max_row = i;
        }
    }

    return max_row;
}


int eliminate(Matrix *mat, Matrix *b) {
    int i, j, k;
    double factor;

    if (mat->r != mat->c || mat->r != b->r || b->c != 1) { 
        fprintf(stderr, "Nieprawidlowe wymiary macierzy! %d x %d, %d, %d\n", mat->r, mat->c, b->r, b->c);
        return 1;
    }

    for (i = 0; i < mat->r - 1; i++) {
        int max_row = find_max_in_col(mat, i, i);
        if (max_row != i) 
	{
            swap_rows(mat, b, i, max_row);
        }

       
        if (fabs(mat->data[max_row][i]) < 1e-12) {
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
    if (fabs(mat->data[mat->r - 1][mat->c - 1]) < 1e-12) {
        fprintf(stderr, "Macierz osobliwa - dzielenie przez 0!\n");
        return 1;
    }

    return 0;
}

