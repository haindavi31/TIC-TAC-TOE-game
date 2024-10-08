#include <iostream>

using namespace std;

const int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE];

// Initialize the board with numbers 1 to 9
void initializeBoard() {
    char num = '1';
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = num++;
        }
    }
}

// Display the current state of the board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << " " << board[i][j];
            if (j < BOARD_SIZE - 1) cout << " |";
        }
        if (i < BOARD_SIZE - 1) cout << "\n---|---|---\n";
    }
    cout << "\n";
}

// Check if a player has won
bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Check if the board is full (draw)
bool checkDraw() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

// Switch player
void switchPlayer(char& currentPlayer) {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Update the board with the player's move
bool makeMove(char player, int move) {
    int row = (move - 1) / BOARD_SIZE;
    int col = (move - 1) % BOARD_SIZE;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = player;
        return true;
    } else {
        return false; // Invalid move
    }
}

int main() {
    char currentPlayer = 'X';
    int move;
    bool gameWon = false, gameDraw = false;
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        // Initialize game
        initializeBoard();
        gameWon = false;
        gameDraw = false;
        currentPlayer = 'X';

        while (!gameWon && !gameDraw) {
            // Display the board
            displayBoard();
            
            // Prompt the current player for a move
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> move;

            // Validate and update the board
            if (move < 1 || move > 9 || !makeMove(currentPlayer, move)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            // Check for win or draw
            gameWon = checkWin(currentPlayer);
            if (gameWon) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
            } else {
                gameDraw = checkDraw();
                if (gameDraw) {
                    displayBoard();
                    cout << "It's a draw!\n";
                } else {
                    switchPlayer(currentPlayer);
                }
            }
        }

        // Ask if the players want to play again
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing!\n";
    return 0;
}
