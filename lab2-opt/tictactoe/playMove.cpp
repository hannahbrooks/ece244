//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h"
#include "gameState.h"
#include <fstream>
#include <cstdio>

// Function prototype for function getWinCode
// Takes one argument of type gameState
// Return type of integer
int getWinCode(gameState);  

void playMove(gameState& game_state)
{
    // Check if the clicked cell is empty
    if (game_state.get_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn()) == 0)
    {
        game_state.set_moveValid(true); // Set moveValid to true
        
        // Set the cell to either a 1 if turn is true, or -1 if turn is false
        game_state.set_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn(), game_state.get_turn() ? 1 : -1);
        // Switch the turn to the other player
        game_state.set_turn(!game_state.get_turn());
        
        int winCode = getWinCode(game_state); // Get the current win code after the preceding move
        // Check if there is a win
        printf("%d", winCode);
        if (winCode != 0)
        {
            game_state.set_winCode(winCode); // Set the win code
            game_state.set_gameOver(true); // End the game
        } else
        {
            // If there is not a win, check if is cat's game
            bool gameOver = true; // Flag variable that will be lowered if the game is still going on
            for (int i = 0; i < boardSize; i++)
            {
                for (int j = 0; j < boardSize; j++)
                {
                    if (game_state.get_gameBoard(i, j) == 0)
                    { // If a cell is still empty, meaning a player can still play
                        gameOver = false;
                    }
                }
            }
            if (gameOver) game_state.set_gameOver(true); // If the loop is exited and the flag is not lowered, end the game
        }
    }    
    else
    {
        game_state.set_moveValid(false); // If the move is invalied set moveValid to false
    }
}

// Initialization of function getWinCode
int getWinCode (gameState game_state)
{
    // Declaring and initializing top row of cells
    int top_l = game_state.get_gameBoard(0, 0); // Top  row, left column
    int top_m = game_state.get_gameBoard(0, 1); // Top row, middle column
    int top_r = game_state.get_gameBoard(0, 2); // Top row, right column

    // Declaring and initializing middle row of cells
    int middle_l = game_state.get_gameBoard(1, 0); // Middle row, left column
    int middle_m = game_state.get_gameBoard(1, 1); // Middle row, middle column
    int middle_r = game_state.get_gameBoard(1, 2); // Middle row, right column
    
    // Declaring and initializing bottom row of cells
    int bottom_l = game_state.get_gameBoard(2, 0); // Bottom row, left column
    int bottom_m = game_state.get_gameBoard(2, 1); // Bottom row, middle column
    int bottom_r = game_state.get_gameBoard(2, 2); // Bottom row, right column
        
    if ((top_l == top_m) && (top_l == top_r) && (top_l != 0)) // If all cells in the top row are equal and non-zero
    {
        return 1;
    } else if ((middle_l == middle_m) && (middle_l == middle_r) && (middle_l != 0)) // If all cells in the middle row are equal and non-zero
    {
        return 2;
    } else if ((bottom_l == bottom_m) && (bottom_l == bottom_r) && (bottom_l != 0)) // If all cells in the bottom row are equal and non-zero
    {
        return 3;
    } else if ((top_l == middle_l) && (top_l == bottom_l) && (top_l != 0)) // If all cells in the left column are equal and non-zero
    {
        return 4;
    } else if ((top_m == middle_m) && (top_m == bottom_m) && (top_m != 0)) // If all cells in the middle column are equal and non-zero
    {
        return 5;
    } else if ((top_r == middle_r) && (top_r == bottom_r) && (top_r != 0)) // If all cells in the right column are equal and non-zero
    {
        return 6;
    } else if ((top_l == middle_m) && (top_l == bottom_r) && (top_l != 0)) // If all cells in the left-to-right diagonal are equal and non-zero
    {
        return 7;
    } else if ((top_r == middle_m) && (top_r == bottom_l) && (top_r != 0)) // If all cells in the right-to-left diagonal are equal and non-zero
    {
        return 8;
    } else
    {
        return 0; // If none of the above cases are true, the game is still going on or it is cat's game
    } 
}

