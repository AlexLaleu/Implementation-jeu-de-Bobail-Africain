int get_column_pos(int** board, int piece, int BOARD_SIZE){
    int x=board[0][0];
    for(int i=0; i<=4; i++){
        for(int j=0; j<=4; j++){
            x = board[i][j];
            if(x == piece) return j;
        }
    }
}

int get_row_pos(int** board, int piece, int BOARD_SIZE){
    int x=board[0][0];
    for(int i=0; i<=4; i++){
        for(int j=0; j<=4; j++){
            x = board[i][j];
            if(x == piece) return i;
        }
    }
}