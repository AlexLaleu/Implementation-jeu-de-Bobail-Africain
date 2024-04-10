#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test_end.h"
#include "get.h"

int test_end(int** board,int size,int current_player){ //doit renvoyer 0 si le jeu continue, le numéro du joueur gagnant sinon
    
    int i=get_row_pos(board,-1,size);
    int j=get_column_pos(board,-1,size);
    if(i==0){return 1;}
    if(i==4){return 2;}
    if(j==0){
        if( (board[i-1][j]!=0) && (board[i+1][j]!=0) && (board[i-1][j+1]!=0) && (board[i][j+1]!=0) && (board[i+1][j+1]!=0) ) {return current_player;}
    }
    if(j==4){
        if( (board[i-1][j]!=0) && (board[i+1][j]!=0) && (board[i-1][j-1]!=0) && (board[i][j-1]!=0) && (board[i+1][j-1]!=0) ) {return current_player;}
    }
    return 0;
}