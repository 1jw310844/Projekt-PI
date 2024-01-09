﻿#include <iostream>
#include <vector>
using namespace std;

class Board {
public:
    Board() : board(3, vector<char>(3, ' ')), currentPlayer('X') {} //vector dynamiczna tablica. Początkowy ruch "X"

    void printBoard() const {
        for (const auto& row : board) {
            for (char cell : row) {
                cout << cell << " | ";
            }
            cout << '\n';
            cout << "---------\n";
        }
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') { //Nieprawidłowy ruch
            return false; // Invalid move
        }

        board[row][col] = currentPlayer; //służy do aktualizacji planszy gry po wykonaniu ruchu przez gracza
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; //Sprawdza, czy aktualny gracz to 'X'.
        return true; // Valid move
    }

    char checkWinner() const {
        // Check rows, columns, and diagonals
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
                return board[i][0]; // Row
            }
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
                return board[0][i]; // Column
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            return board[0][0]; // Diagonal
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
            return board[0][2]; // Diagonal
        }

        return ' '; // No winner yet
    }

    bool isBoardFull() const {
        for (const auto& row : board) { //pracujemy z referencja a nie kopią
            for (char cell : row) {
                if (cell == ' ') {
                    return false; // Board is not full
                }
            }
        }
        return true; // Board is full
    }

private:
    vector<vector<char>> board;
    char currentPlayer;
};

int main() {
    Board gameBoard;

    do {
        gameBoard.printBoard();

        int row, col;
        cout << "Gracz " << gameBoard.checkWinner() << ", wykonaj ruch (wiersz , kolumna): ";
        cin >> row >> col;

        if (gameBoard.makeMove(row, col)) {
            if (gameBoard.checkWinner() != ' ') {
                cout << "Gracz " << gameBoard.checkWinner() << " wygrywa!\n";
                break;
            }
            else if (gameBoard.isBoardFull()) {
                cout << "Remis!\n";
                break;
            }
        }
        else {
            cout << "Nieprawidłowy ruch. Spróbuj ponownie.\n";
        }
    } while (true);

    gameBoard.printBoard();

    return 0;
}