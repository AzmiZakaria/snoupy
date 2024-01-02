

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