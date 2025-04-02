#include <stdio.h>
#include <stdbool.h>

#define N 4 // Change this for different board sizes

// Function to print the board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N-Queens
bool solveNQueens(int board[N][N], int row) {
    if (row == N) { // If all queens are placed, print the board
        printBoard(board);
        return true;
    }

    bool foundSolution = false;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place queen
            foundSolution = solveNQueens(board, row + 1) || foundSolution;
            board[row][col] = 0; // Backtrack (remove queen)
        }
    }

    return foundSolution;
}

int main() {
    int board[N][N] = {0}; // Initialize board with zeros
    if (!solveNQueens(board, 0))
        printf("No solution exists.\n");
    return 0;
}