
//function.c
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void initializeGameBoard(char gameBoard[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameBoard[i][j] = ' ';
        }
    }
}

void placeElementOnBoard(char gameBoard[ROWS][COLS], Position pos, char symbol) {
    gameBoard[pos.x][pos.y] = symbol;
}

void displayGameBoard(char gameBoard[ROWS][COLS]) {
    hideCursor();
    COORD cursorPos;  // Structure pour stocker la position du curseur
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
    printf("|------------------------------------------------------------------|\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", gameBoard[i][j]);
        }
        printf("|\n");
    }
    printf("|------------------------------------------------------------------|\n");
    // showCursor();
}

void moveBall(Ball *ball) {
    // Mesurer le temps actuel
    clock_t currentTime = clock();

    // Vérifier si le délai minimum (en millisecondes) s'est écoulé depuis le dernier déplacement
    if ((currentTime - lastMoveTime) > 20) {  // 100 millisecondes, ajustez selon votre préférence
        // Logique de déplacement de la balle (diagonale vers le bas et vers la droite)
        ball->pos.x = (ball->pos.x < ROWS - 1) ? ball->pos.x + 1 : 0;
        ball->pos.y = (ball->pos.y < COLS - 1) ? ball->pos.y + 1 : 0;

        // Mettre à jour le dernier temps de déplacement
        lastMoveTime = currentTime;
    }
}

void updateGameState(char gameBoard[ROWS][COLS], Snopy *snoopy, Ball *ball, Obstacle *obstacle, Oiseau *oiseau) {
    // Effacer les anciennes positions
    placeElementOnBoard(gameBoard, snoopy->pos, ' ');
    placeElementOnBoard(gameBoard, ball->pos, ' ');
    placeElementOnBoard(gameBoard, obstacle->pos, ' ');
    placeElementOnBoard(gameBoard, oiseau->pos, ' ');

    // Mettre à jour les positions
    moveBall(ball);
    // moveObstacle(obstacle);
    // moveOiseau(oiseau);

    // Gérer les collisions

    // Afficher les nouvelles positions
    placeElementOnBoard(gameBoard, snoopy->pos, snoopy->symbol);
    placeElementOnBoard(gameBoard, ball->pos, ball->symbol);
    placeElementOnBoard(gameBoard, obstacle->pos, obstacle->symbol);
    placeElementOnBoard(gameBoard, oiseau->pos, oiseau->symbol);

    displayGameBoard(gameBoard);
}

void moveSnopy(Snopy *snoopy, char direction) {
    switch (direction) {
        case 72:  // Haut
            snoopy->pos.x = (snoopy->pos.x > 0) ? snoopy->pos.x - 1 : snoopy->pos.x;
            break;
        case 80:  // Bas
            snoopy->pos.x = (snoopy->pos.x < ROWS - 1) ? snoopy->pos.x + 1 : snoopy->pos.x;
            break;
        case 75:  // Gauche
            snoopy->pos.y = (snoopy->pos.y > 0) ? snoopy->pos.y - 1 : snoopy->pos.y;
            break;
        case 77:  // Droite
            snoopy->pos.y = (snoopy->pos.y < COLS - 1) ? snoopy->pos.y + 1 : snoopy->pos.y;
            break;
    }
}
void menu(){
    printf("Menu:\n");
    printf("1. Règles du jeu\n");
    printf("2. Lancer niveau\n");
    printf("3. Charger une partie\n");
    printf("4. Scores\n");
    printf("5. Quitter\n");

}
void saveGameBoardToFile(char gameBoard[ROWS][COLS], const char *fileName) {
    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour la sauvegarde.\n");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Convertir les caractères spéciaux en codes spécifiques lors de l'écriture
            switch (gameBoard[i][j]) {
                case 0x2:
                    fprintf(file, "S ");
                    break;
                case 0xB:
                    fprintf(file, "B ");
                    break;
                case 0xE:
                    fprintf(file, "O ");
                    break;
                case 0xF:
                    fprintf(file, "X ");
                    break;
                // Ajoutez d'autres cas spéciaux si nécessaire
                default:
                    fprintf(file, "%c ",'v');
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void loadGameBoardFromFile(char gameBoard[ROWS][COLS], const char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour le chargement.\n");
        return;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(file, " %c", &gameBoard[i][j]) != 1) {
                printf("Erreur lors de la lecture du fichier.\n");
                fclose(file);
                return;
            }

            // Convertir les codes spéciaux en caractères spéciaux
            switch (gameBoard[i][j]) {
                case 'S':
                    gameBoard[i][j] = 0x2; // Code spécifique pour Snoopy
                    break;
                case 'B':
                    gameBoard[i][j] = 0xB; // Code spécifique pour Ball
                    break;
                case 'O':
                    gameBoard[i][j] = 0xE; // Code spécifique pour Oiseau
                    break;
                case 'X':
                    gameBoard[i][j] = 0xF; // Code spécifique pour Obstacle
                    break;
                default:
                    gameBoard[i][j] = ' '; // Code spécifique pour Obstacle

                // Ajoutez d'autres cas spéciaux si nécessaire
            }
        }
    }

    fclose(file);
}
