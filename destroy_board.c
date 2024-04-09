#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "destroy_board.h"

void destroy_board(int **matrice, int lignes) {
    for (int i = 0; i < lignes; i++) {
        free(matrice[i]);
    }
    free(matrice);
}