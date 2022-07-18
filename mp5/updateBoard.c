// This program in a whole is the famous game of life.
// This particular c file is in place to contruct 3 function to help the game run.
// int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
// This function counts the number of living neighbors surrounding the cell
// void updateBoard(int* board, int boardRowSize, int boardColSize)
// This function is to update the board according to rules
// int aliveStable(int* board, int boardRowSize, int boardColSize)
// This function counts if the alive cells are still the same
// These three functions makes this file.



/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    // number about to return
    int alive = 0;
    // loop counters
    int i,j;
    for(i=row-1;i<=row+1;i++){
        //from previous to current to next
        if((i>=0)&&(i<=boardRowSize-1)){
            // cannot exceed the boarder of the board
            for(j=col-1;j<=col+1;j++){
                //from previous to current to next
                if((j>=0)&&(j<=boardColSize-1)){
                    // cannot exceed the boarder of the board
                    if((board[i*boardColSize+j])&&(i*boardColSize+j!=row*boardColSize+col)){
                        // if the counter is not counting the status of the cell of interest into alive, then we can increment alive
                        alive++;
                    }
                }
            }
        }
    }
    // return int of interest
    return alive;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize){
    // alternative board to do changes in
    int alt_board [boardRowSize*boardColSize]; 
    // loop counters
    int i,j,k,l;
    // for every element we copy into alt_board
    for(i=0;i<boardRowSize*boardColSize;i++){
        int copy = board[i];
        alt_board[i] = copy;
    }
    // logic to fill alt_board with next state values. values input all uses original values
    // row counter
    for(j=0;j<boardRowSize;j++){
        // column counter
        for(k=0;k<boardColSize;k++){
            alt_board[j*boardColSize+k] = 0;
            // count neighbor numbers
            int count_result = countLiveNeighbor(board,boardRowSize,boardColSize,j,k);
            // if conditions correct, alive cell still lives
            if(board[j*boardColSize+k]&&((count_result==2)||(count_result==3))){
                alt_board[j*boardColSize+k] = 1;
            // otherwise it dies
            }else if(board[j*boardColSize+k]){
                alt_board[j*boardColSize+k] = 0;
            }
            // if conditions correct, dead cell res
            if((!board[j*boardColSize+k])&&(count_result==3)){
                alt_board[j*boardColSize+k] = 1;
            }
        }
    }
    // copy alt board countents to main board and return
    for(l=0;l<boardRowSize*boardColSize;l++){
        int copyy = alt_board[l];
        board[l] = copyy;
    }
    return;
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    //counters copied from updateBoard()
    int j,k;
    //row counter
    for(j=0;j<boardRowSize;j++){
        //column counter
        for(k=0;k<boardColSize;k++){
            //store count for reference
            int count_result = countLiveNeighbor(board,boardRowSize,boardColSize,j,k);
            // if such conditions met, must have changed, thus return 0 directly
            if(board[j*boardColSize+k]&&!((count_result==2)||(count_result==3))){
                return 0;
            }
        } 
    }
    //return 1 otherwise
    return 1;
}

				
				
			

