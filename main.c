#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "./headers/head.h"

#define ROWS 10
#define COLS 20
clock_t lastMoveTime = 0;

int main() {
    char gameBoard[ROWS][COLS];
    int choix;    
    char fileName[100];  // ou une taille appropriée selon vos besoins

    Snopy snoopy = {{1, 1}, 0x2};
    Ball ball = {{3, 3}, 0xB};
    Obstacle obstacle = {{5, 5}, 0xF};
    Oiseau oiseau = {{7, 7}, 0xE};

    initializeGameBoard(gameBoard);
    menu();
    printf("Choisissez une option (1-5): ");
    scanf("%d", &choix);

    while (1) {
        switch (choix) {
            case 1 :
                printf("game rules : \n");
                break;
            case 3:
                printf("Entrez le nom du fichier de chargement : ");
                scanf("%s", fileName);
                loadGameBoardFromFile(gameBoard, fileName);
                printf("Matrice chargée depuis le fichier.\n");
            case 2:
                while (1) {
                    updateGameState(gameBoard, &snoopy, &ball, &obstacle, &oiseau);

                    if (snoopy.pos.x == oiseau.pos.x && snoopy.pos.y == oiseau.pos.y) {
                        printf("Félicitations, Snoopy a récupéré l'oiseau!\n");
                        break;
                    }

                    displayGameBoard(gameBoard);

                    printf("Déplacez Snoopy (↑ pour haut, ↓ pour bas, ← pour gauche, → pour droite): ");
                    if (kbhit()) {
                        char direction = _getch();
                        if (direction == 'q' || direction == 'Q') {
                            printf("\nVous avez quitté le jeu.\n");
                            break;
                        } else if (direction == 's' || direction == 'S') {
                            printf("Entrez le nom du fichier de sauvegarde : ");
                            scanf("%s", fileName);
                            saveGameBoardToFile(gameBoard, fileName);
                            printf("Matrice sauvegardée dans le fichier.\n");
                            placeElementOnBoard(gameBoard, snoopy.pos, ' ');
                            break;
                        }
                        placeElementOnBoard(gameBoard, snoopy.pos, ' ');
                        moveSnopy(&snoopy, direction);
                    }
                }

                // Réinitialiser les positions initiales des caractères pour la prochaine itération
                snoopy.pos.x = 1;
                snoopy.pos.y = 1;
                snoopy.symbol = 0x2;

                ball.pos.x = 3;
                ball.pos.y = 3;
                ball.symbol = 0xB;

                obstacle.pos.x = 5;
                obstacle.pos.y = 5;
                obstacle.symbol = 0xF;

                oiseau.pos.x = 7;
                oiseau.pos.y = 7;
                oiseau.symbol = 0xE;
                break;
            case 4:
                // Afficher les scores
                // Ajoutez ici le code pour afficher les scores
                break;

            case 5:
                printf("Au revoir !\n");
                return 0;

            default:
                printf("Option non valide. Veuillez choisir une option entre 1 et 5.\n");
                break;
        }
        menu();
        printf("\nChoisissez une option (1-5): ");
        scanf("%d", &choix);
    }
    return 0;
}
