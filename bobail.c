#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test_end.h"
#include "destroy_board.h"
#include "get.h"
#include "is_legal.h"

#define BOARD_SIZE 5 
// pour la prochaine fois :  print le tableau initial pour vérifier que ca marche




// on va représenter les pions verts par les nombres de 1 à 5 sur le plateau, les pions rouges entre 6 et 10, le pion jaune (BOBAIL) par -1 et les cases vides par 0
// j'utilise la configuration initiale du site https://boulder-nautilus-254.notion.site/Sujet-515cc36d34f54bbdbf2279ea5b0e4c0b (pions verts en haut, pions rouges en bas)
// l'utilisateur va jouer les pions verts, la machine les pions rouges

int main() {
    int** board=(int**)malloc(sizeof(int*)*BOARD_SIZE);
    if(board==NULL){
        printf("error\n");
    }
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(i==0){
                board[i][j] = j+1;
            }
            if(i==4){
                board[i][j] = j+6;
            }
            if((i==2)&&(j==2)){
                board[i][j] = -1;
            }
            else{
                board[i][j] = 0;
            }
        }
    }

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
                int column_index = column - 'A' + 1;
                int row_index = row-1;
                int row_pos = get_row_pos(board, piece, BOARD_SIZE);
                int column_pos = get_column_pos(board, piece, BOARD_SIZE);
                if(is_legal(board,-1,row_pos, column_pos, column_index,row_index)==false){
                    printf("erreur, coup non légal\n");
                    break;
                }
                modify_board(&board,-1,column_index,row_index);
            }


            printf("quel pion voulez-vous jouer ? (entrez un chiffre entre 1 et 5 inclu)\n");
            scanf("%d",&piece);
            if((piece<1)||(piece>5)){
                printf("erreur, veuillez entrer un chiffre valide !\n");
                break;
            }
            printf("à quelles coordonnée voulez-vous le déplacer ? (exemple A2, respectez la majuscule) \n");
            scanf("%c%d",&column,&row);
            int column_index = column - 'A' + 1;
            int row_index = row-1;
            if((column_index<0)||(column_index>4)||(row_index<0)||(row_index>4)){
                printf("erreur, veuillez entrer une coordonnée valide !\n");
                break;
            }
            int row_pos = get_row_pos(board, piece, BOARD_SIZE);
            int column_pos = get_column_pos(board, piece, BOARD_SIZE);
            if(is_legal(board,piece,row_pos,column_pos,column_index,row_index) == false){
                printf("erreur, coup non légal\n");
                break;
            }
            modify_board(&board,piece,column_index,row_index);
            swap(&current_opponent,&current_player);
            }

            if(current_player==2){ // "l'intelligence artificielle" sur-entraînée joue ici
                srand(time(NULL));

                //il joue le bobail (il le joue dans tous les cas car c'est le joueur humain qui commence au tout début)
                int random_row = rand()%BOARD_SIZE;
                int random_column = rand()%BOARD_SIZE;
                int row_pos = get_row_pos(board, -1, BOARD_SIZE);
                int column_pos = get_column_pos(board, -1, BOARD_SIZE);
                while(!is_legal(board,-1,row_pos,column_pos,random_column,random_row)){
                    random_column = rand()%BOARD_SIZE;
                    random_row = rand()%BOARD_SIZE;
                }
                modify_board(&board,-1,random_column,random_row);
                
                // il joue sa  pièce :
                int random_piece = rand()%5 + 6;
                int row_pos = get_row_pos(board, random_piece, BOARD_SIZE);
                int column_pos = get_column_pos(board, random_piece, BOARD_SIZE);
                while(!is_legal(board,-1,row_pos,column_pos,random_column,random_row)){
                    random_column = rand()%BOARD_SIZE;
                    random_row = rand()%BOARD_SIZE;
                }
                modify_board(&board,random_piece,random_column,random_row);
                swap(&current_opponent,&current_player);
            }
    }
    int winner=test_end(board);
    if(winner == 1){
        printf("bravo vous avez gagné !\n");
    }
    else(winner == 2){
        printf("dommage, la machine vous a battu.\n");
    }
    destroy(board,BOARD_SIZE);
    return 0;
}