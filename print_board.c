#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void print_board(int** board,int BOARD_SIZE) {
    printf("Plateau de jeu :\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf("  "); // Case vide
            } else if (board[i][j] >= 1 && board[i][j] <= 5) {
                printf("X "); // Croix
            } else if (board[i][j] >= 6 && board[i][j] <= 10) {
                printf("O "); // Rond
            } else if (board[i][j] == -1) {
                printf("B "); // B
            }
        }
        printf("\n");
    }
}