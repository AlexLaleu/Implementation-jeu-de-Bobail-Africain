#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test_end.h"
#include "print_board.h"
#include "modify_board.h"
#include "is_legal_bis.h"

#define BOARD_SIZE 5 
int main() {

    int** board = (int**)malloc(sizeof(int*) * BOARD_SIZE);
    if (board == NULL) {
        printf("Erreur lors de l'allocation mémoire\n");
        return 1;
    }

    // Allocation de mémoire pour chaque ligne de la matrice
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = (int*)malloc(sizeof(int) * BOARD_SIZE);
        if (board[i] == NULL) {
            printf("Erreur lors de l'allocation mémoire\n");
            return 1;
        }
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(i == 0) {
                board[i][j] = j + 1;
            } else if(i == 4) {
                board[i][j] = j + 6;
            } else if(i == 2 && j == 2) {
                board[i][j] = -1;
            } else {
                board[i][j] = 0;
            }
        }
    }
    printf("plateau initial : \n");
    print_board(board,BOARD_SIZE);
    /*board[0][0]=1;
    board[1][0]=-1;
    board[1][1]=6;
    board[2][1]=7;
    board[2][0]=8;
    board[4][0]=0;
    board[4][1]=0;
    board[4][2]=0;*/
    if(is_legal_bis(board,-1,2,3,BOARD_SIZE)){ //légal
        modify_board(&board,-1,2,3,BOARD_SIZE);
        print_board(board,BOARD_SIZE);
    }
    if(is_legal_bis(board,1,2,2,BOARD_SIZE)){ //illégal
        modify_board(&board,1,2,2,BOARD_SIZE);
        print_board(board,BOARD_SIZE);
    }
    if(is_legal_bis(board,1,3,3,BOARD_SIZE)){ //légal
        modify_board(&board,1,3,3,BOARD_SIZE);
        print_board(board,BOARD_SIZE);
    }
    if(is_legal_bis(board,2,2,2,BOARD_SIZE)){ // illégal
        modify_board(&board,2,2,2,BOARD_SIZE);
        print_board(board,BOARD_SIZE);
    }
    if(is_legal_bis(board,3,0,1,BOARD_SIZE)){ // illégal
        modify_board(&board,3,0,1,BOARD_SIZE);
        print_board(board,BOARD_SIZE);
    }
    if(is_legal_bis(board,5,3,4,BOARD_SIZE)){
        modify_board(&board,5,3,4,BOARD_SIZE);
        print_board(board,BOARD_SIZE);
    }
    return 0;
}