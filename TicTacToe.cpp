#include <iostream>
#include <vector>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"

void drawBoard(const std::vector<std::vector<char>> &board)
{
    std::cout << "  0   1   2\n"; // Column indices
    for (int i = 0; i < 3; ++i)
    {
        std::cout << i << " "; // Row index
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == 'X')
                std::cout << RED << board[i][j] << RESET;
            else if (board[i][j] == 'O')
                std::cout << BLUE << board[i][j] << RESET;
            else
                std::cout << " ";
            if (j < 2) std::cout << " | "; // Vertical divider
        }
        std::cout << "\n";
        if (i < 2) std::cout << " ---+---+---\n"; // Horizontal divider
    }
}


bool checkWin(const std::vector<std::vector<char>> &board, char player)
{
  for (int i = 0; i < 3; ++i)
  {
      if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
          (board[0][i] == player && board[1][i] == player && board[2][i] == player))
      {
          return true;
      }
  }

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[0][2] == player && board[1][1] == player && board[2][0] == player))
  {
      return true;
  }

  return false;
}

bool checkDraw(const std::vector<std::vector<char>> &board)
{
  for (const auto &row : board)
  {
      for (char cell : row)
      {
          if (cell == ' ')
          {
              return false;
          }
      }
  }
  return true;
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}


int main() {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
    char currentPlayer = 'X';
    int row, col;
    bool gameOver = false;

    while (!gameOver) {
        clearScreen();
        drawBoard(board);
        std::cout << "Player " << currentPlayer << ", enter row and column (0-2): ";
        std::cin >> row >> col;

        if (board[row][col] == ' ')
        {
            board[row][col] = currentPlayer;
            gameOver = checkWin(board, currentPlayer);

            if (gameOver)
            {
                drawBoard(board);
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
            }
            else if (checkDraw(board))
            {
                drawBoard(board);
                std::cout << "It's a draw!" << std::endl;
                gameOver = true;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        else
        {
            std::cout << "That spot is already taken. Try again." << std::endl;
        }
    }

  return 0;
}