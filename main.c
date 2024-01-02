#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "./headers/head.h"

#define ROWS 10
#define COLS 20
clock_t lastMoveTime = 0;


int kbhit(void) {
    return _kbhit();
}

int main() {
    char gameBoard[ROWS][COLS];
    initializeGameBoard(gameBoard);

    Snopy snoopy = {{1, 1}, 0x2};
    Ball ball = {{3, 3}, 0xB};
    Obstacle obstacle = {{5, 5}, 0xF};
    Oiseau oiseau = {{7, 7}, 0xE};

    while (1) {
        updateGameState(gameBoard, &snoopy, &ball, &obstacle, &oiseau);

        if (snoopy.pos.x == oiseau.pos.x && snoopy.pos.y == oiseau.pos.y) {
            printf("Félicitations, Snoopy a récupéré l'oiseau!\n");
            break;
        }

        printf("Déplacez Snoopy (↑ pour haut, ↓ pour bas, ← pour gauche, → pour droite): ");
        if (kbhit()) {
            char direction = _getch();
            if (direction == 'q' || direction == 'Q') {
                printf("\nVous avez quitté le jeu.\n");
                break;
            }
            placeElementOnBoard(gameBoard, snoopy.pos, ' ');
            moveSnopy(&snoopy, direction);
        }
        displayGameBoard(gameBoard);
    }

    return 0;
}



