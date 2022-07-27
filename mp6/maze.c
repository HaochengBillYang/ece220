#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//Intro Paragraph
//The following functions takes part in solving a maze, their particular funtions are as follows:
//1. createMaze -- Creates and fills a maze structure from the given file
//2. destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
//3. printMaze --  Prints out the maze in a human readable format (should look like examples)
//4. solveMazeDFS -- recursively solves the maze using depth first search
//The following program is tested using gold testcases and valgrind to make sure destroy maze is successful
//



/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int i, j; // Initiate counters
    int w, h; // Initiate width and height
    FILE *fileptr;// pointer for maze file
    maze_t * maze = (maze_t *)malloc(sizeof(maze_t)); // memory allocation for the maze
    char start = 'S', end = 'E'; // S and E for start and end.
    fileptr = fopen(fileName, "r"); //open file as read
    fscanf(fileptr, "%d %d", &w, &h); //find width and hright of the maze
    maze->width = w; //store width and height
    maze->height = h;
    fgetc(fileptr); //gets to new line
    maze->cells = (char **)malloc(w*sizeof(char*)); //allocate the cells
    for(i=0; i<h; i++){
        maze->cells[i] = (char*)malloc(w*sizeof(char));
    }
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            fscanf(fileptr, "%c", &maze->cells[i][j]); //read value and store in cells
            if(maze->cells[i][j]==start){
                maze->startColumn = j;  //start is i and j if S is reached
                maze->startRow = i;
            }else if(maze->cells[i][j]==end){
                maze->endColumn = j;    //end is i and j if E is reached
                maze->endRow = i;
            }
        }
        fgetc(fileptr); //for eac loop there is a new line char
    }
    fclose(fileptr);    //close the file

    return maze; //return maze with attributes filled
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i; //initialize a row counter
    for(i=0; i<maze->height;i++){
        free(maze->cells[i]); //free all the rows, effectively everything in the array cells
    }
    free(maze->cells); //free the array cells
    free(maze); //free the maze itself
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j; // initialize row and column counters
    for(i=0; i<maze->height; i++){
        for(j=0; j<maze->width; j++){
            printf("%c", maze->cells[i][j]); //print every cell iteritively
        }
    printf("\n"); //new line after each row is printed
    }
}

/*
 * solveMazeDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    // base case 1: Invalid spots / return false
    if(row < 0 || row >= maze->height || col < 0 || col >= maze->width){
        return 0;
    }else if(maze->cells[row][col] == WALL || maze->cells[row][col] == PATH || maze->cells[row][col] == VISITED){
        return 0;
    }
    // base case 2: This spot is the end / return true
    else if(maze->cells[row][col] == END){
        maze -> cells[maze -> startRow][maze -> startColumn] = START; // restore start sign
        return 1;
    }
    // give path char, start recursive case
    if(maze->cells[row][col] != END){
        maze -> cells[row][col] = PATH;
    }
    // Try four directions
    if(solveMazeDFS(maze, col-1, row)){
        return 1;
    }
    if(solveMazeDFS(maze, col, row+1)){
        return 1;
    }
    if(solveMazeDFS(maze, col+1, row)){
        return 1;
    }
    if(solveMazeDFS(maze, col, row-1)){
        return 1;
    }
    // if until now no solution is found, this is not a possible cell, thus mark as visited and never visit again
    if(maze-> cells[row][col]!=START && maze -> cells[row][col]!=END)
    {
        maze-> cells[row][col]=VISITED;
    }

    return 0;
}
