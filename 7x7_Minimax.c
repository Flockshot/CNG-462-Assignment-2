#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#define SIZE 7

struct TicTacToe
{
    char board[SIZE][SIZE];
    char playerChar;
    char AIChar;
    int score;
};
typedef struct TicTacToe TicTacToe;

struct Move
{
    int x;
    int y;
};
typedef struct Move Move;


TicTacToe *createGame();
char getPlayerChar();

void playPlayerTurn(TicTacToe *game);

void playAITurn(TicTacToe* game);

Move* alphaBetaSearch(TicTacToe* game);
int max(TicTacToe* game, Move *move, int  alpha, int beta);
int min(TicTacToe* game, Move *move, int  alpha, int beta);

int checkWin(TicTacToe* game, char player);




int isBoardFull(TicTacToe* game);
int evaluateBoard(TicTacToe* game);



void printBoard(TicTacToe *game);

void calcTime();


int checkBoardStatus(TicTacToe *game);

int main()
{

    TicTacToe *game = createGame();
    int continueGame = 1;
    printBoard(game);

    while(continueGame)
    {
        playPlayerTurn(game);
        printBoard(game);
        continueGame = checkBoardStatus(game);

        if(!continueGame)
            break;

        clock_t start = clock();
        // Call the Minimax algorithm to calculate the next move
        playAITurn(game);
        clock_t end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Elapsed time: %f\n", elapsed_time);

        printBoard(game);
        continueGame = checkBoardStatus(game);
    }



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

    while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || game->board[row][col] != '_')
    {
        printf("Enter the row and column for your move with no overlap eg: (0 0): ");
        scanf(" %d %d", &row, &col);
    }


    game->board[row][col] = game->playerChar;
}


void playAITurn(TicTacToe* game)
{
    Move *move = alphaBetaSearch(game);
    game->board[move->x][move->y] = game->AIChar;

}


Move* alphaBetaSearch(TicTacToe* game)
{
    Move *move = (Move *) malloc(sizeof(Move));

    printf("score=%d\n", max(game, move, INT_MIN, INT_MAX));
    printf("x=%d\n", move->x);
    printf("y=%d\n", move->y);

    return move;
}

int max(TicTacToe* game, Move *move, int  alpha, int beta)
{
    if (checkWin(game, game->playerChar))
        return -1; // Player wins
    else if (checkWin(game, game->AIChar))
        return 1;
    else if (isBoardFull(game))
        return 0;

    int maxScore = INT_MIN;
    int bestMoveX = -1;
    int bestMoveY = -1;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game->board[i][j] == '_')
            {
                game->board[i][j] = game->AIChar;
                int currentScore = min(game, move, alpha, beta);

                //printf("score=%d\n", currentScore);
                //printf("x=%d\n", bestMoveX);
                //printf("y=%d\n", bestMoveY);
                //printBoard(game);

                //reverting the change back, so our original board is not changed.
                game->board[i][j] = '_';

                //TODO CHCECK FOR WHAT MOVE IT WILL BE
                if (currentScore > maxScore)
                {
                    bestMoveX = i;
                    bestMoveY = j;
                    maxScore = currentScore;

                    alpha = alpha>maxScore ? alpha : maxScore;
                }
                if(maxScore >= beta)
                {
                    move->x = bestMoveX;
                    move->y = bestMoveY;
                    return maxScore;
                }
            }
        }
    }

    move->x = bestMoveX;
    move->y = bestMoveY;

    return maxScore;
}

int min(TicTacToe* game, Move *move, int  alpha, int beta)
{
    if (checkWin(game, game->playerChar))
        return -1; // Player wins
    else if (checkWin(game, game->AIChar))
        return 1;
    else if (isBoardFull(game))
        return 0;

    int minScore = INT_MAX;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game->board[i][j] == '_')
            {
                game->board[i][j] = game->playerChar;
                int currentScore = max(game, move, alpha, beta);
                game->board[i][j] = '_';

                if (currentScore < minScore)
                {
                    minScore = currentScore;
                    beta = beta<minScore ? beta : minScore;
                }
                if(minScore <= alpha)
                    return minScore;
            }
        }
    }

    return minScore;
}

/*
int getBestMove(TicTacToe* game)
{
    int bestScore = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game->board[i][j] == '_')
            {
                game->board[i][j] = game->AIChar;
                int currentScore = minimax(game, 0, 0);
                game->board[i][j] = '_';

                if (currentScore > bestScore) {
                    bestScore = currentScore;
                    bestMove = i * SIZE + j;
                }
            }
        }
    }

    return bestMove;
}
*/













int checkWin(TicTacToe* game, char player)
{
    //Checks board horizontally
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y <= SIZE - 4; y++)
        {
            int horizontal = 1;

            for(int z = y; z < SIZE && z < y+4; z++)
                horizontal = horizontal && player == game->board[x][z];

            if (horizontal)
                return 1;
        }
    }

    //Checks board vertically
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x <= SIZE - 4; x++)
        {
            int vertical = 1;

            for(int z = x; z < SIZE && z < x+4; z++)
                vertical = vertical && player == game->board[z][y];

            if (vertical)
                return 1;
        }
    }
    /*
    //Checks board diagonally
    for (int x = 0; x <= SIZE - 4; x++)
    {
        int diagonal = 1;

        for(int z = x; z < SIZE && z < x+4; z++)
            diagonal = diagonal && player == game->board[z][z];

        if (diagonal)
            return 1;
    }

    for (int x = 0; x <= SIZE - 4; x++)
    {
        int diagonal1 = 1;

        for(int z = x; z < SIZE && z < x+4; z++)
            diagonal1 = diagonal1 && player == game->board[z][(SIZE-1)-z];

        if (diagonal1)
            return 1;
    }
    */
    for (int x = 0; x < SIZE - 3; x++)
    {
        for (int y = 0; y < SIZE - 3; y++)
        {
            int diagonal = 1;
            for (int z = 0; z < 4; z++)
            {
                if (game->board[x + z][y + z] != player)
                {
                    diagonal = 0;
                    break;
                }
            }
            if (diagonal)
                return 1;

        }
    }

    // Check diagonally (top-right to bottom-left)
    for (int x = 0; x < SIZE - 3; x++)
    {
        for (int y = 3; y < SIZE; y++)
        {
            int diagonal1 = 1;
            for (int z = 0; z < 4; z++)
            {
                if (game->board[x + z][y - z] != player)
                {
                    diagonal1 = 0;
                    break;
                }
            }
            if (diagonal1)
                return 1;
        }
    }

    return 0;
}




int isBoardFull(TicTacToe* game)
{
    int i;
    int j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (game->board[i][j] == '_')
                return 0;
    return 1;
}

//TODO CHECK HOW THE UTILITY IS USED.
int evaluateBoard(TicTacToe* game)
{
    if (checkWin(game, game->playerChar))
        return -1; // Player wins
    else if (checkWin(game, game->AIChar))
        return 1; // AI wins
    else
        return 0; // Draw
}

int checkBoardStatus(TicTacToe *game)
{
    if(isBoardFull(game))
    {
        printf("Its a draw!\n");
        return 0;
    }
    else
    {
        switch(evaluateBoard(game))
        {
            case -1:
                printf("You won!\n");
                return 0;
            case 1:
                printf("You lost!\n");
                return 0;
        }
    }

    return 1;
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


