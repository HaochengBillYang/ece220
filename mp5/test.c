#include <stdlib.h>
#include <stdio.h>
#include "updateBoard.h"
#include "updateBoardGold.h"

int main(){
	int row,col,step;
	step = 0;
	row = 18;
	col = 35;
	int i,j;
	int *game_board_stu = malloc(sizeof(int) * 18 * 35);
	int *game_board_gold = malloc(sizeof(int) * 18 * 45);
	int initial[18*35] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(i = 0; i < 18*35; i++)
	{
		game_board_gold[i] = initial[i];
		game_board_stu[i] = initial[i];
	}
	int stuCount,goldCount;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			stuCount = countLiveNeighbor(game_board_stu, row, col, i, j);
			goldCount = countLiveNeighbor_gold(game_board_gold,row,col,i,j);
			if(stuCount != goldCount){
				printf("countLiveNeighbor test failed\n");
				free(game_board_gold);
				free(game_board_stu);
				return 0;
			}
		}
	}
	printf("countLiveNeighbor test passed\n");
	step = 0;
	while(!aliveStable_gold(game_board_gold, row, col)){
		if(step > 10000){
			printf("updateBoard test passed\n");
			printf("aliveStable test not finished due to too many steps taken\n");
		}
		if(aliveStable(game_board_stu,row,col)){
			printf("aliveStable test failed\n");
			free(game_board_gold);
			free(game_board_stu);
			return 0;
		}
		updateBoard_gold(game_board_gold,row,col);
		updateBoard(game_board_stu,row,col);
		for(i=0;i<row;i++){
			for(j=0;j<col;j++){
				if(game_board_stu[i*col+j]!= game_board_gold[i*col+j]){
					printf("updateBoard test failed\n");
					free(game_board_gold);
					free(game_board_stu);
					return 0;
				}
			}
		}
	}
	if(!aliveStable(game_board_stu,row,col)){
		printf("aliveStable test failed\n");
		free(game_board_gold);
		free(game_board_stu);
		return 0;
	}
	printf("updateBoard test passed\n");
	printf("aliveStable test passed\n");
	free(game_board_gold);
	free(game_board_stu);
	return 0;
}
