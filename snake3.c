#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover, key, score, paused;
int x, y;

// New variables for 3 apples
int fruitx[3], fruity[3];
int applesEaten; 

// New variables for speed
int gameSpeed; // 1 = Slow, 2 = Fast

// --- FUNCTION DECLARATIONS ---
void setup();
void draw();
void input();
void logic();
void saveGame();
void loadGame();

void setup() {
    srand(time(NULL));
    gameover = 0;
    score = 0;
    snakeTailLen = 0;
    applesEaten = 0;
    paused = 0;
    
    x = WIDTH / 2;
    y = HEIGHT / 2;
    key = 0; 

    // Generate 3 apples initially
    for (int i = 0; i < 3; i++) {
        fruitx[i] = rand() % (WIDTH - 2) + 1;
        fruity[i] = rand() % (HEIGHT - 2) + 1;
    }
}

// Helper to generate 3 new apples
void generateApples() {
    for (int i = 0; i < 3; i++) {
        fruitx[i] = rand() % (WIDTH - 2) + 1;
        fruity[i] = rand() % (HEIGHT - 2) + 1;
    }
    applesEaten = 0; // Reset the counter
}

void draw() {
    clear();

    for (int i = 0; i < WIDTH + 2; i++) printw("-");
    printw("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH) {
                printw("#");
            }
            if (i == y && j == x) {
                printw("O"); 
            } else {
                int isFruit = 0;
                // Draw 3 fruits
                for (int f = 0; f < 3; f++) {
                    if (i == fruity[f] && j == fruitx[f]) {
                        printw("*");
                        isFruit = 1;
                        break;
                    }
                }
                
                if (!isFruit) {
                    int prTail = 0;
                    for (int k = 0; k < snakeTailLen; k++) {
                        if (snakeTailX[k] == j && snakeTailY[k] == i) {
                            printw("o"); 
                            prTail = 1;
                            break;
                        }
                    }
                    if (!prTail) printw(" ");
                }
            }
        }
        printw("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printw("-");
    printw("\nScore: %d | Apples Eaten: %d/3\n", score, applesEaten);
    printw("Speed: %s (Press '1' for Slow, '2' for Fast)\n", (gameSpeed == 1) ? "Slow" : "Fast");
    printw("Controls: Arrow Keys or 'z' for UP | 'w' for DOWN | 'q' for LEFT | 'd' for RIGHT | \n 's' to Save | 'l' to Load | 'p' to Pause | 'x' to Quit\n");
    if (paused){
        printw("\n***GAME PAUSED - PRESS P TO RESUME ****\n");
    }
    refresh();
}

void input() {
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    int ch = getch();
    
    if (ch != ERR) {
        switch (ch) {
            // Arrow Keys
            case KEY_LEFT:  if(key != 2) key = 1; break;
            case KEY_RIGHT: if(key != 1) key = 2; break;
            case KEY_UP:    if(key != 4) key = 3; break;
            case KEY_DOWN:  if(key != 3) key = 4; break;
            
            // QDZW
            case 'q': if(key != 2) key = 1; break;
            case 'd': if(key != 1) key = 2; break;
            case 'z': if(key != 4) key = 3; break;
            case 'w': if(key != 3) key = 4; break;
            
            // Speed controls
            case '1': gameSpeed = 1; break;
            case '2': gameSpeed = 2; break;

            // Pause / Unpause
            case 'p': paused = !paused; break;
            
            // Save / Load / Quit
            case 's': saveGame(); break;
            case 'l': loadGame(); break; // 'l' for Load
            case 'x': gameover = 1; break;
        }
    }
}

void logic() {
    
    if (paused) return;
    // logic for tail
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    //direction movement
    switch (key) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }
    //wall collision
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;
    //tail collision

    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    // Check eating all 3 apples
    for (int i = 0; i < 3; i++) {
        if (x == fruitx[i] && y == fruity[i]) {
            score += 10;
            applesEaten++;
            
            // Remove this apple by moving it off-screen
            fruitx[i] = -1; 
            fruity[i] = -1;
            
            // If all 3 are eaten, grow and generate new ones
            if (applesEaten == 3) {
                snakeTailLen+= 3;
                generateApples();
            }
            break; 
        }
    }
}

// --- SAVE AND LOAD FUNCTIONS ---
void saveGame() {
    FILE *f = fopen("savegame.txt", "w");
    if (f == NULL) return;
    
    fprintf(f, "%d %d %d %d %d %d\n", x, y, snakeTailLen, score, applesEaten, key);
    for (int i = 0; i < snakeTailLen; i++) {
        fprintf(f, "%d %d\n", snakeTailX[i], snakeTailY[i]);
    }
    for (int i = 0; i < 3; i++) {
        fprintf(f, "%d %d\n", fruitx[i], fruity[i]);
    }
    fclose(f);
    
    // Show a quick message
    mvprintw(HEIGHT + 6, 0, "Game Saved!");
    refresh();
}

void loadGame() {
    FILE *f = fopen("savegame.txt", "r");
    if (f == NULL) {
        mvprintw(HEIGHT + 6, 0, "No save file found!");
        refresh();
        return;
    }
    
    fscanf(f, "%d %d %d %d %d %d", &x, &y, &snakeTailLen, &score, &applesEaten, &key);
    for (int i = 0; i < snakeTailLen; i++) {
        fscanf(f, "%d %d", &snakeTailX[i], &snakeTailY[i]);
    }
    for (int i = 0; i < 3; i++) {
        fscanf(f, "%d %d", &fruitx[i], &fruity[i]);
    }
    fclose(f);

    key = 0; //snake doesn't move until play presses a key
    paused =  1; // the game is paused

    mvprintw(HEIGHT + 6, 0, "Game Loaded!");
    refresh();
    usleep(15000000); // 
}

int main() {
    initscr(); 
    curs_set(0); 
    noecho();    

    gameSpeed = 1; // Default to Slow
    setup();

    // --- CHECK FOR SAVE FILE AT STARTUP ---
    FILE *check = fopen("savegame.txt", "r");
    clear();
    if (check != NULL) {
        fclose(check);
        mvprintw(HEIGHT / 2, WIDTH / 2 - 15, "Save file detected!");
        mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 15, "Press 'l' to Load, or play normally.");
    } else {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 15, "No save file found.");
        mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - 15, "Starting a new game.");
        
    }
    refresh();
    usleep(3000000);

    while (!gameover) {
        draw();
        input();
        if (!paused && key != 0){ //run only when not paused
            logic();
        }
        if (paused){
            usleep(1000000);
        }

        // Apply speed logic
        if (gameSpeed == 1) {
            usleep(200000); // Slow: 200ms
        } else {
            usleep(80000);  // Fast: 80ms
        }
    }
    
    endwin(); 
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}