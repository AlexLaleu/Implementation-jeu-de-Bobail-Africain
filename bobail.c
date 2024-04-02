#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 5

void destroy(int **matrice, int lignes) {
    for (int i = 0; i < lignes; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

bool is_legal(int** board,int piece, int column_index, int row_index){
    // doit renvoyer true si le coup est légal, false sinon. Attention faire disjonction de cas si la piece est le pion jaune ou non
}

int test_end(int** board){
    //doit renvoyer 0 si le jeu continue, le numéro du joueur gagnant sinon
}

void modify_board(int*** board, int piece, int column_index, int row_index){
    // modifie board pour prendre en compte le coup joué (le coup est supposé légal ici)
}

void swap(int* p_a, int* p_b){
    int temp = *p_a;
    *p_a = *p_b;
    *p_b=temp;
}



// on va représenté les pions verts par les nombres de 1 à 5 sur le plateau, les pions rouges entre 6 et 10, le pion jaune (BOBAIL) par -1 et les cases vides par 0
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
    while(test_end(board) == 0){

        if(current_player==1){

            char column;
            int row;
            int piece;

            if(cmpt!=0){     // celui qui entame la partie n’avance que l’un de ses pions (le mouvement du BOBAIL est sauté).
                printf("où voulez-vous déplacer le BOBAIL ? (exemple A2, respectez la majuscule)\n");
                scanf("%c%d",&column,&row);
                int column_index = column - 'A' + 1;
                int row_index = row-1;
                if(is_legal(board,-1,column_index,row_index)==false){
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
            if(is_legal(board,piece,column_index,row_index) == false){
                printf("erreur, coup non légal\n");
                break;
            }
            modify_board(&board,column_index,row_index);
            swap(&current_opponent,&current_player);
            }

            if(current_player==2){
                // "l'intelligence artificielle" sur-entraînée joue ici
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