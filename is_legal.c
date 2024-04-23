#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


bool is_legal(int** board,int piece, int row_pos, int column_pos, int column_index, int row_index){
    // doit renvoyer true si le coup est légal, false sinon. Attention faire disjonction de cas si la piece est le pion jaune ou non
    if(piece!=-1){

        if(row_index == row_pos && column_pos == column_index) return false;   //immobile : interdit

        if(board[row_index][column_index]!=0) return false;       //pas de place

        if(   ( (abs(column_index-column_pos)) != (abs(row_index-row_pos)) ) && (row_index!=row_pos) && (column_index!=column_pos)   ) return false;  //si le depl n'est ni en ligne ni en colonne, ce doit être une vraie diagonale

        if(row_pos == row_index){         //depl sur une ligne
            if(column_index>column_pos){           //vers la droite
                if(column_index != 4 && board[row_index][column_index+1]==0) return false;  //Si on ne va pas au bout d'une ligne et qu'aucun pion nous en empêche, c'est pas correct
                for(int i=1; i <= column_index-column_pos; i++){
                    if(board[row_pos][column_pos+i]!=0) return false;
                }
            }
            if(column_index<column_pos){           //vers la gauche
                if(column_index != 4 && board[row_index][column_index-1]==0) return false;
                for(int i=1; i <= column_pos-column_index; i++){
                    if(board[row_pos][column_pos-i]!=0) return false;
                }
            }
        }

        if(column_pos == column_index){    //depl sur une colonne
            if(row_index>row_pos){                  //vers le bas
                if(row_index != 4 && board[row_index+1][column_index]==0) return false;
                for(int i=1; i <= row_index-row_pos; i++){
                    if(board[row_pos+i][column_pos]!=0) return false;
                }
            }
            if(row_index<row_pos){                  //vers le haut
                if(row_index != 4 && board[row_index-1][column_index]==0) return false;
                for(int i=1; i <= row_pos-row_index; i++){
                    if(board[row_pos-i][column_pos]!=0) return false;
                }
            }
        }

        else{    //depl sur une diagonale
            if(column_index!=4 && column_index!=0 && row_index != 4 && row_index != 0){
                if(column_index>column_pos && row_index>row_pos){
                    if(board[row_index+1][column_index+1]==0) return false;
                    for(int i=1; i <= column_index-column_pos; i++){
                        if(board[row_pos+i][column_pos+i]!=0) return false;
                    }
                }
                if(column_index>column_pos && row_index<row_pos){
                    if(board[row_index-1][column_index+1]==0) return false;
                    for(int i=1; i <= column_index-column_pos; i++){
                        if(board[row_pos-i][column_pos+i]!=0) return false;
                    }
                }
                if(column_index<column_pos && row_index>row_pos){
                    if(board[row_index+1][column_index-1]==0) return false;
                    for(int i=1; i <= row_index-row_pos; i++){
                        if(board[row_index+i][column_index-i]!=0) return false;
                    }
                }
                if(column_index<column_pos && row_index<row_pos){
                    if(board[row_index-1][column_index-1]==0) return false;
                    for(int i=1; i <= row_pos-row_index; i++){
                        if(board[row_index-i][column_index-i]!=0) return false;
                    }
                }
            }
        }
    }
    else{
        if(  (abs(column_index-column_pos) >1) || (abs(row_index-row_pos) >1)  ) return false;

        if(board[row_index][column_index]!=0) return false;
    }
    return true;
}
