#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "get.h"
#include "is_path_empty.h"


bool is_legal_bis(int **board,int piece, int row, int column, int size){
    int current_row=get_row_pos(board,piece,size);
    int current_column=get_column_pos(board,piece,size);

    
//test si il déplace bien la piece
    if( (current_row==row) && (current_column==column) ){
        return false;
    }

//test si le pion ne passe que par des cases vides
    if(!is_path_empty(board,current_row,current_column,row,column)){
        return false;
    }

//déplacement d'un pion
    if(piece!=-1){
    
    // déplacement en diagonale
        if( ( abs(current_row-row)== abs(current_column-column) ) && (row<5) && (row<5) ){ 
            if((column==0) || (column==4) || (row==0) || (row==4)){
                return true;
            }
            if((current_row<row)&&(current_column<column)){
                if(board[row+1][column+1]!=0){
                    return true;
                }
            }
            if((current_row<row)&&(current_column>column)){
                if(board[row+1][column-1]!=0){
                    return true;    
                }
            }
            if((current_row>row)&&(current_column>column)){
                if(board[row-1][column-1]!=0){
                    return true;
                }
            }
            if((current_row>row)&&(current_column<column)){
                if(board[row-1][column+1]!=0){
                    return true;
                }
            }
        }
        
    // deplacement sur une colonne
        if(current_column==column){
            if((row==0)||(row==4)){
                return true;
            }

            if(current_row<row){
                if(board[row+1][column]!=0){
                    return true;
                }
            }
            if(current_row>row){
                if(board[row-1][column]!=0){
                    return true;
                }
            }
        } 

    // deplacement sur une ligne
        if(current_row==row){
            if((column==0)||(column==4)){
                return true;
            }

            if(current_column<column){
                if(board[row][column+1]!=0){
                    return true;
                }
            }
            if(current_column>column){
                if(board[row][column-1]!=0){
                    return true;
                }
            }
        } 
    }

//déplacement du bobail
    if(piece==-1){
        if( (abs(current_column-column)<=1) && (abs(current_row-row)<=1) ){
                return true;
        }
    }
    return false;
}