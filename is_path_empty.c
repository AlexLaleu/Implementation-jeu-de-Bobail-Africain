#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_path_empty(int** board, int current_row, int current_column, int row, int column) {
    // Vérification si le déplacement est sur la même ligne, colonne ou diagonale
    if (current_row != row && current_column != column && abs(current_row - row) != abs(current_column - column))
        return false;

    // déplacement en diagonale
    if( abs(current_row-row) == abs(current_column-column) ){
        if((current_row<row)&&(current_column<column)){
            for(int i=1;i<=abs(current_row-row);i++){
                if(board[current_row+i][current_column+i]!=0){
                    return false;
                }
            }
        }
        if((current_row<row)&&(current_column>column)){
            for(int i=1;i<=abs(current_row-row);i++){
                if(board[current_row+i][current_column-i]!=0){
                    return false;
                }
            }
        }
        if((current_row>row)&&(current_column>column)){
            for(int i=1;i<=abs(current_row-row);i++){
                if(board[current_row-i][current_column-i]!=0){
                    return false;
                }
            }
        }
        if((current_row>row)&&(current_column<column)){
            for(int i=1;i<=abs(current_row-row);i++){
                if(board[current_row-i][current_column+i]!=0){
                    return false;
                }
            }
        }
    }

    //déplacement en colonne
    if(current_column==column){
        if(current_row<row){
            for(int i=1;i<=abs(current_row-row);i++){
                if(board[current_row+i][current_column]!=0){
                    return false;
                }
            }
        }
        if(current_row>row){
            for(int i=1;i<=abs(current_row-row);i++){
                if(board[current_row-i][current_column]!=0){
                    return false;
                }
            }
        }
    }

    //déplacement sur une ligne
    if(current_row==row){
        if(current_column<column){
            for(int i=1;i<=abs(current_column-column);i++){
                if(board[current_row][current_column+i]!=0){
                    return false;
                }
            }
        }
        if(current_row>row){
            for(int i=1;i<=abs(current_column-column);i++){
                if(board[current_row][current_column-i]!=0){
                    return false;
                }
            }
        }
    }


    // Vérifier si la case finale est vide
    return (board[row][column] == 0);
}