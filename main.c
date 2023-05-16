#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#define SIZE 3

struct TicTacToe
{
    char board[SIZE][SIZE];
    char playerChar;
    char AIChar;
    int score;
};
typedef struct TicTacToe TicTacToe;



TicTacToe *createGame();
char getPlayerChar();

void playPlayerTurn(TicTacToe *game);
void getPlayerPosition(int *row, int *col);



void printBoard(TicTacToe *game);

void calcTime();




int main()
{



    TicTacToe *game = createGame();

    printBoard(game);

    playPlayerTurn(game);

    printBoard(game);




    printf("Hello, World!\n");
    return 0;
}

TicTacToe *createGame()
{
    TicTacToe *game = (TicTacToe *) malloc(sizeof(TicTacToe));

    int i;
    int j;

    for(i=0; i<SIZE; i++)
        for(j=0; j<SIZE; j++)
            game->board[i][j] = '_';



    game->playerChar = getPlayerChar();
    game->AIChar = (game->playerChar == 'X') ? 'O' : 'X';

    //TODO REMOVE
    game->score = 0;

    return game;
}

char getPlayerChar()
{
    char playerChar = ' ';

    while (playerChar != 'X' && playerChar != 'O')
    {
        printf("Select your character X or O: ");
        scanf(" %c", &playerChar);
        playerChar = toupper(playerChar);
    }

    printf("You selected: %c\n", playerChar);
    return playerChar;
}

void playPlayerTurn(TicTacToe *game)
{
    int row = -1;
    int col = -1;

    getPlayerPosition(&row, &col);

    game->board[row][col] = game->playerChar;
}

void getPlayerPosition(int *row, int *col)
{
    while (*row < 0 || *row >= SIZE || *col < 0 || *col >= SIZE)
    {
        printf("Enter the row and column for your move (0 0): ");
        scanf(" %d %d", row, col);
    }
}



void printBoard(TicTacToe *game)
{

    printf("-------------\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            printf("| %c ", game->board[i][j]);

        printf("|\n");
        printf("-------------\n\n");
    }
}


void calcTime()
{
    clock_t start = clock();

    // Call the Minimax algorithm to calculate the next move
    //int score = minimax(board, 0, true);

    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f\n", elapsed_time);
}


