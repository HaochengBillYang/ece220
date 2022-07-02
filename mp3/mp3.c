/*
This program calculates the pascal triangle from lines 1 to 41 (0-40 with 0 indexing)
When user enters one number, it echoes it to screen, then prints that line of the pascal triangle
The design is a bit different than specified in mp3, but results are the same
*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int row;

    printf("Enter a row index: ");
    scanf("%d",&row);

    // Write your code here
    // following code creates a 41x41 unsigned long 2D array, filled with 0.
    // This 2D array is to store values in the pascal triangle <= 40.
    unsigned long dict[41][41];
    for (int i = 0; i <= 40; i++)
    {
        for (int j = 0; j <= 40; j++)
        {
            dict[i][j] = 0;
        }

    }

    // following code loops through the values in the 2D array
    // gives 1 to starting and ending entires
    // gives all other the sum of the previous row, same column and previous row previous column
    for (int i = 0; i <= 40; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            dict[i][0] = 1;
            dict[i][i] = 1;
            if(j != 0 && j != i){
                dict[i][j] = dict[i-1][j]+ dict[i-1][j-1];
            }
        }

    }

    // following code is the output of the program
    // prints the row specified by int row
    // prints element and then puts space in the end of each
    // line change at the end, since in mp page the output does not show the current directory
    for (int j = 0; j <= 40; j++)
    {   
        if (dict[row][j] != 0){
            printf("%lu ", dict[row][j]);
        }
    }
    printf("\n");


    // visualizing debugger, uncomment to print the whole triangle
    /*
    for (int i = 0; i <= 40; i++)
    {
        for (int j = 0; j <= 40; j++)
        {   
            if (dict[i][j] != 0){
                printf("%lu ",dict[i][j]);
            }
        }
        printf("\n");
    }
    */

    return 0;
}