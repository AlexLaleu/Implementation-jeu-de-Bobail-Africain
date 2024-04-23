#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "modify_board.h"
#include "get.h"

void modify_board(int*** board, int piece, int row_index, int column_index, int size){
    int i=get_row_pos(*board,piece,size);
    int j=get_column_pos(*board,piece,size);
    (*board)[i][j]=0;
    (*board)[row_index][column_index] = piece;
}
