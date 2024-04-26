#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "test_end.h"
#include "destroy_board.h"
#include "get.h"
#include "swap.h"
#include "modify_board.h"
#include "is_legal_bis.h"
#include "print_board.h"
#include "destroy_board.h"
#include "is_path_empty.h"

#define BOARD_SIZE 5 
// pour la prochaine fois : 
//is_legal_bis semble beuger quand c'est l'ordinateur qui joue. Peut-etre une erreur dans sa boucle



// on va représenter les pions verts par les nombres de 1 à 5 sur le plateau, les pions rouges entre 6 et 10, le pion jaune (BOBAIL) par -1 et les cases vides par 0
// j'utilise la configuration initiale du site https://boulder-nautilus-254.notion.site/Sujet-515cc36d34f54bbdbf2279ea5b0e4c0b (pions verts en haut, pions rouges en bas)
// l'utilisateur va jouer les pions verts, la machine les pions rouges

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
                board[i][j] = j + BOARD_SIZE+1;
            } else if(i == BOARD_SIZE/2 && j == BOARD_SIZE/2) {
                board[i][j] = -1;
            } else {
                board[i][j] = 0;
            }
        }
    }
    printf("plateau initial : \n\n");
    print_board(board,BOARD_SIZE);
    int current_player = 1; // le joueur humain commence
    int current_opponent = 2;
    int cmpt=0;
    while(test_end(board,BOARD_SIZE,current_player) == 0){

        if(current_player==1){

            char column;
            int row;
            int piece;

            if(cmpt!=0){     // celui qui entame la partie n’avance que l’un de ses pions (le mouvement du BOBAIL est sauté).
                printf("où voulez-vous déplacer le BOBAIL ? (exemple A2, respectez la majuscule)\n");
                scanf("%c%d",&column,&row);
                int column_index = column - 'A';
                int row_index = row-1;
                while(is_legal_bis(board,-1,row_index, column_index,BOARD_SIZE)==false){
                    printf("erreur, coup non légal\n");
                    printf("où voulez-vous déplacer le BOBAIL ? (exemple A2, respectez la majuscule)\n");
                    scanf("%c%d",&column,&row);
                    column_index = column - 'A' ;
                    row_index = row-1;
                }
                modify_board(&board,-1,row_index,column_index,BOARD_SIZE);
                print_board(board,BOARD_SIZE);
            }


            int column_index=0;
            int row_index=0;
            do{
                printf("quel pion voulez-vous jouer ? (entrez un chiffre entre 1 et 5 inclus)\n");
                scanf(" %d",&piece);
                if (piece < 1 || piece > 5){
                    printf("erreur, veuillez entrer un chiffre entre 1 et 5 !\n");
                }
            }while((piece<1)||(piece>5));
            
            do{
                printf("à quelles coordonnée voulez-vous le déplacer ? (exemple A2, respectez la majuscule) \n");
                scanf(" %c%d",&column,&row);
                column_index = column - 'A';
                row_index = row-1;
                if((column_index<0)||(column_index>4)||(row_index<0)||(row_index>4)){
                    printf("erreur, veuillez entrer une coordonnée valide !\n");
                }
                if(is_legal_bis(board,piece,row_index,column_index,BOARD_SIZE) == false){
                    printf("erreur, coup non légal, entrez de nouvelles coordonnées\n");
                }
                
            }while(((column_index<0)||(column_index>4)||(row_index<0)||(row_index>4)) || (is_legal_bis(board,piece,row_index,column_index,BOARD_SIZE) == false));

            modify_board(&board,piece,row_index,column_index,BOARD_SIZE);
            print_board(board,BOARD_SIZE);
            swap(&current_opponent,&current_player);
            cmpt++;
            if(test_end(board,BOARD_SIZE,current_player) == 1){
                break;
            }
            }


            if(current_player==2){ // "l'intelligence artificielle" sur-entraînée joue ici
                srand(time(NULL));

                //il joue le bobail (il le joue dans tous les cas car c'est le joueur humain qui commence au tout début)
                int random_row = rand()%BOARD_SIZE;
                int random_column = rand()%BOARD_SIZE;
                do{
                    random_column = rand()%BOARD_SIZE;
                    random_row = rand()%BOARD_SIZE;
                }while(!is_legal_bis(board,-1,random_row,random_column,BOARD_SIZE));
                modify_board(&board,-1,random_row,random_column,BOARD_SIZE);
                print_board(board,BOARD_SIZE);
                
                // il joue sa  pièce :
                int random_piece;
                do{
                    random_piece = rand()%5 + 6;
                    random_column = rand()%BOARD_SIZE;
                    random_row = rand()%BOARD_SIZE;
                    if((is_legal_bis(board,random_piece,random_row,random_column,BOARD_SIZE)==false)){
                        printf("l'ordinateur s'est trompé il a voulu bougé %d en (%d,%d)\n",random_piece,random_row+1,random_column+1);
                    }
                }while(is_legal_bis(board,random_piece,random_row,random_column,BOARD_SIZE)==false);

                printf("l'ordinateur bouge %d en (%d,%d) : \n\n",random_piece,random_row+1,random_column+1);
                modify_board(&board,random_piece,random_row,random_column,BOARD_SIZE);
                print_board(board,BOARD_SIZE);
                swap(&current_opponent,&current_player);
            }
    }
    int winner=test_end(board,BOARD_SIZE,current_player);
    if(winner == 1){
        printf("bravo vous avez gagné !\n");
    }
    else{
        printf("dommage, la machine vous a battu.\n");
    }
    destroy_board(board,BOARD_SIZE);
    return 0;
}