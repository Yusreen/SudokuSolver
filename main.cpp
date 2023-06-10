/*
This program uses Backtracking and recursion to solve a sudoku.
It was inspired from: cppsecrets.com
*/


#include <iostream>
#define N 9
using namespace std;


int grid[N][N] = {
    {6,5,0,8,7,3,0,9,0},
    {0,0,3,2,5,0,0,0,8},
    {9,8,0,1,0,4,3,5,7},
    {1,0,5,0,0,0,0,0,0},
    {4,0,0,0,0,0,0,0,2},
    {0,0,0,0,0,0,5,0,3},
    {5,7,8,3,0,1,0,2,6},
    {2,0,0,0,4,8,9,0,0},
    {0,9,0,6,2,5,0,8,1}
};


/**
 * This function is used to check if an number is in a specific row
*/
 bool checkIfNumIsPresentInColumn (int num, int col)
 {
   for (int row=0; row<N; row++)
      if(grid[row][col]==num)
         return true;
    
  return false;
 } // end of checkIfNumIsPresentInColumn 

 /**
 * This function is used to check if an number is in a specific row
 */
 bool checkIfNumIsPresentInRow (int num, int row)
 {
   for (int col=0; col<N; col++)
     if(grid[row][col]==num)
       return true;

return false;
 } // end of checkIfNumIsPresentInRow


 /**
  * This function is used to check if a number is present in the 3x3 box
 */

bool checkifNumIsPresentInBox (int boxStartRow,int boxStartCol,int num)
{

    for (int row=0; row <3; row++)
        for (int col=0; col <3;col++)
            if(grid[row+boxStartRow][col+boxStartCol]==num)
               return true;
        
    
    return false;

}// end of checkifNumIsPresentInBox 

/**
 * This function is used to check if there are any empty spots in the sudoku
 * It returns the index of the first empty spot
*/
bool findIndexOfFirstEmptySpot (int &row, int &col) //reference is used rather than copying
{
    for (row=0; row <N;row++)
        for (col=0; col <N; col++)
           if (grid[row][col]== 0)
              return true;
        
    return false;
}

/**
 * This function is used to check if the move is legal in a specific spot
*/

bool isLegalMove (int row,int col, int num)
{
   return  !checkIfNumIsPresentInColumn (num, col)&& 
            !checkIfNumIsPresentInRow (num, row) &&
            !checkifNumIsPresentInBox (row - row%3 , col - col%3, num);
       
}

/**
 * This function is used to print the sudoku
*/
void printSudokuGrid() {   
   for (int row = 0; row < N; row++) {
      cout<<"[ ";
      for (int col = 0; col < N; col++) {
        
         cout << grid[row][col] <<" ";
      }
      cout<<"]"<<endl;

      }
      cout << endl;
   
}// end of printSudokuGrid


/*
* This function is used to solve the sudoku
*/
bool solveSudokuGrid()
{
    //Create the row and column
    int row, col;

   //Check if the sudoku is incomplete first
    if(!findIndexOfFirstEmptySpot(row,col))
    {
        return true;
    }
    //Start the solving process
    for (int num=1; num<=9; num++)
    {
        if(isLegalMove(row,col, num)) //if the number can be added to the spot
        {
           grid[row][col]=num; //solve that spot
        
        if(solveSudokuGrid()) //Solve the rest of the empty spots recursively.
           return true;

        grid[row][col]=0; //Backtrack
        }
    }

    return false;

}//end of solveSudokuGrid

int main() {
   if (solveSudokuGrid() == true)
      printSudokuGrid();
   else
      cout << "No solution exists";
}