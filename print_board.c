#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

#include <stdio.h>

void print_board(int** board, int BOARD_SIZE) {
    printf("\nPlateau de jeu :\n");
    printf(" ");
    // Affichage des lettres pour les colonnes en bleu
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("\033[34m %c\033[0m", 'A' + col);
    }
    printf("\n");

    // Affichage des lignes
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("\033[34m%d \033[0m", i + 1); // Numérotation des lignes en bleu
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf("  "); // Case vide
            } else if (board[i][j] >= 1 && board[i][j] <= 5) {
                printf("\033[32m\u25CF\033[0m "); // Rond en vert (\u25CF représente un cercle plein)
            } else if (board[i][j] >= 6 && board[i][j] <= 10) {
                printf("\033[31m\u2B24\033[0m "); // Rond en rouge (\u25CF représente un cercle plein)
            } else if (board[i][j] == -1) {
                printf("\033[33mB\033[0m  "); // B en jaune
            }
        }
        printf("\n");
    }
    printf("\n");
}