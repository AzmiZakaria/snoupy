#define ROWS 10
#define COLS 20
extern clock_t lastMoveTime;

#include "../functions/caracters.c"
#include "../functions/function.c"

void initializeGameBoard(char gameBoard[ROWS][COLS]);

void placeElementOnBoard(char gameBoard[ROWS][COLS], Position pos, char symbol);

void updateGameState(char gameBoard[ROWS][COLS], Snopy *snoopy, Ball *ball, Obstacle *obstacle, Oiseau *oiseau);

void displayGameBoard(char gameBoard[ROWS][COLS]);

void moveBall(Ball *ball);

void moveSnopy(Snopy *snoopy, char direction);

void hideCursor();

void showCursor();