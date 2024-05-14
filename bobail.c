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
                printf("Où voulez-vous déplacer le BOBAIL ? (exemple A2, respectez la majuscule)\n\n");
                scanf("%c%d",&column,&row);
                int column_index = column - 'A';
                int row_index = row-1;

                do{
                    printf("Où voulez-vous déplacer le BOBAIL ? (exemple A2, respectez la majuscule)\n\n");
                    scanf("%c%d",&column,&row);
                    column_index = column - 'A' ;
                    row_index = row-1;
                    if(is_legal_bis(board,-1,row_index, column_index,BOARD_SIZE)==false){
                        printf("Erreur, coup non légal\n\n");
                    }
                }while(is_legal_bis(board,-1,row_index, column_index,BOARD_SIZE)==false);

                modify_board(&board,-1,row_index,column_index,BOARD_SIZE);
                print_board(board,BOARD_SIZE);
            }


            int column_index=0;
            int row_index=0;
            do{
                if (cmpt==0) printf("Bienvenue dans cette interface vous permettant de vous amuser gratuitement et librement au jeu du Bobail africain !\n\n");
                if (cmpt==0) printf("Vous commencez la partie, et vos pions sont les verts : lequel voulez-vous jouer ? (entrez un chiffre entre 1 et 5 inclus, les pions sont numérotés de la gauche vers la droite)\n\n");
                else printf("Quel pion voulez-vous jouer ? (entrez un chiffre entre 1 et 5 inclus)\n\n");
                scanf(" %d",&piece);
                if (piece < 1 || piece > 5){
                    printf("Erreur, veuillez entrer un chiffre entre 1 et 5 !\n\n");
                }
            }while((piece<1)||(piece>5));
            
            do{
                printf("A quelles coordonnée voulez-vous le déplacer ? (exemple A2, respectez la majuscule) \n\n");
                scanf(" %c%d",&column,&row);
                column_index = column - 'A';
                row_index = row-1;
                if((column_index<0)||(column_index>4)||(row_index<0)||(row_index>4)){
                    printf("Erreur, veuillez entrer une coordonnée valide !\n\n");
                }
                if(is_legal_bis(board,piece,row_index,column_index,BOARD_SIZE) == false){
                    int z = rand() % 2 + 1;
                    if (z==1) printf("Erreur, coup non légal, entrez de nouvelles coordonnées.\n\n");
                    if (z==2) printf("On va pas s'énerver, entrez de nouvelles coordonnées pour un coup légal svp.\n\n");
                }
                
            }while(((column_index<0)||(column_index>4)||(row_index<0)||(row_index>4)) || (is_legal_bis(board,piece,row_index,column_index,BOARD_SIZE) == false));

            modify_board(&board,piece,row_index,column_index,BOARD_SIZE);
            print_board(board,BOARD_SIZE);
            swap(&current_opponent,&current_player);
            cmpt++;
            if(test_end(board,BOARD_SIZE,current_player) != 0){
                break;
            }
            }


            if(current_player==2){ 
                srand(time(NULL));

                //il joue le bobail (il le joue dans tous les cas car c'est le joueur humain qui commence au tout début)
                int random_row = rand()%BOARD_SIZE;
                int random_column = rand()%BOARD_SIZE;
                do{
                    random_column = rand()%BOARD_SIZE;
                    random_row = rand()%BOARD_SIZE;
                }while(!is_legal_bis(board,-1,random_row,random_column,BOARD_SIZE));
                char c = random_column + 1 + 64;
                int x = rand() % 6 + 1;

                if (x==1) printf("L'ordinateur déplace le bobail en %c%d : \n\n",c,random_row+1);
                if (x==2) printf("Superbe coup de la machine qui place le bobail en %c%d ! \n\n",c,random_row+1);
                if (x==3) printf("Coup très rapide de l'ordinateur qui bouge le bobail en %c%d : \n\n",c,random_row+1);
                if (x==4) printf("La machine vient étonnamment déplacer le bobail en %c%d ... \n\n",c,random_row+1);
                if (x==5) printf("Et le bobail passe maintenant en %c%d ... Quelle vivacité de la part de l'adversaire ! \n\n",c,random_row+1);
                if (x==6) printf("L'ordinateur met le bobail en %c%d ! \n\n",c,random_row+1);

                modify_board(&board,-1,random_row,random_column,BOARD_SIZE);
                print_board(board,BOARD_SIZE);
                
                // il joue sa  pièce :
                int random_piece;
                do{
                    random_piece = rand()%5 + 6;
                    random_column = rand()%BOARD_SIZE;
                    random_row = rand()%BOARD_SIZE;
                }while(is_legal_bis(board,random_piece,random_row,random_column,BOARD_SIZE)==false);
                c = random_column + 1 + 64;
                int y = rand() % 8 + 1;

                if (y==1) printf("L'ordinateur bouge %d en %c%d : \n\n",random_piece,c,random_row+1);
                if (y==2) printf("L'adversaire déplace minutieusement %d en %c%d . Il semble préparer sa stratégie... \n\n",random_piece,c,random_row+1);
                if (y==3) printf("Coup très stratégique de la machine qui place subtilement %d en %c%d ! \n\n",random_piece,c,random_row+1);
                if (y==4) printf("L'ordinateur déplace %d en %c%d . Quelle finesse ! \n\n",random_piece,c,random_row+1);
                if (y==5) printf("On ne s'y attendait pas, le pion %d passe en %c%d : quel coup surprenant ! \n\n",random_piece,c,random_row+1);
                if (y==6) printf("Saviez-vous que l'enseigne des bureaux de tabac représente une carotte ? Bref, %d bouge en %c%d : \n\n",random_piece,c,random_row+1);
                if (y==7) printf("L'ordinateur déplace %d en %c%d ... Comme disait mon prof de prépa, que du calcul, aucun recul ! \n\n",random_piece,c,random_row+1);
                if (y==8) printf("L'ordinateur gère bien son espace sur le plateau en installant %d en %c%d : \n\n",random_piece,c,random_row+1);

                modify_board(&board,random_piece,random_row,random_column,BOARD_SIZE);
                print_board(board,BOARD_SIZE);
                swap(&current_opponent,&current_player);
            }
    }
    int winner=test_end(board,BOARD_SIZE,current_player);
    if(winner == 1){
        printf("Bravo, vous avez gagné ! Ceci étant fait...\n\n");
    }
    else{
        printf("Dommage, la machine vous a battu. Snif snif\n\n");
    }
    destroy_board(board,BOARD_SIZE);
    return 0;
}