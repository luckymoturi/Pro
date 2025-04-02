#include <stdio.h>
#include <stdlib.h>  // Include this for abs()
#define N 8  

void printSolution(int board[N]) {
    for (int i = 0; i < N; i++, printf("\n"))
        for (int j = 0; j < N; j++)
            printf("%c ", board[i] == j ? 'Q' : '.');
    printf("\n");
}

int isSafe(int board[N], int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i] == col || abs(board[i] - col) == row - i)
            return 0;
    return 1;
}

void solveNQueens(int board[N], int row) {
    if (row == N) {
        printSolution(board);
        return;
    }
    for (int col = 0; col < N; col++)
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(board, row + 1);
        }
}

int main() {
    int board[N] = {0};
    solveNQueens(board, 0);
    return 0;
}
