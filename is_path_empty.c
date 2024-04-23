#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_path_empty(int** board, int current_row, int current_column, int row, int column) {
    // Vérification si le déplacement est sur la même ligne, colonne ou diagonale
    if (current_row != row && current_column != column && abs(current_row - row) != abs(current_column - column))
        return false;

    // Déterminer le sens du déplacement
    int delta_row = (row > current_row) ? 1 : ((row < current_row) ? -1 : 0);
    int delta_column = (column > current_column) ? 1 : ((column < current_column) ? -1 : 0);

    // Vérifier chaque case le long du chemin
    int r = current_row + delta_row;
    int c = current_column + delta_column;
    while (r != row || c != column) {
        if (board[r][c] != 0)
            return false;
        r += delta_row;
        c += delta_column;
    }

    // Vérifier si la case finale est vide
    return (board[row][column] == 0);
}