#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;
    return true;
}

void printSolution(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                cout << " Q" << i+1 ;
            else
                cout << " 0 ";
        }
        cout << endl;
    }
    cout << endl;
}

bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    if (row == N) {
        printSolution(board, N);
        return true;
    }
    bool success = false;

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;

            success = solveNQueens(board, row + 1, N) || success;

            board[row][col] = 0;
        }
    }
    return success;
}

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0, N)) {
        cout << "No solution exists for " << N << " queens." << endl;
    }
    return 0;
}

// time complexity:o(n*n!)
// space=o(n)