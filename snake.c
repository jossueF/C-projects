#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define HEIGHT 20
#define WIDTH 80

void setup();
void drawGame();
void addSnake(); 
int * printSnakeChunk();
int controls();


int *posSnakeChunk;


typedef struct{
    int posX;
    int posY;
    int sizeSnake;
    char *body;
}Snake;
Snake *snake;

void setup(){
    system("cls");

    snake = malloc(sizeof(Snake));
    snake -> posX = WIDTH / 2;
    snake -> posY = HEIGHT / 2;
    snake -> sizeSnake = 1;
    snake -> body = calloc(1, sizeof(char));
    snake -> body[0] = '@';

    posSnakeChunk = calloc(2, sizeof(int));
    posSnakeChunk = printSnakeChunk();
}

int main(void){
    setup();
    while(1){
        drawGame();
        controls();
    }
    

    free(snake -> body);
    free(snake);
    free(posSnakeChunk);

    return EXIT_SUCCESS;
}

void drawGame(){
    printf("****************** SNAKE ******************\n");
    printf("w = UP, s = DOWN, a = LEFT, d = RIGHT, exit = ESC\n");

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1){
                printf("%c", '#');
            }
            else if(snake -> posX == j && snake -> posY == i){
                for(int k = 0; k < snake -> sizeSnake; k++){
                    printf("%c", snake -> body[k]);
                }
            }
            else if(posSnakeChunk[0] == j && posSnakeChunk[1] == i){
                printf("%c", 'p');
            }
            else{
                printf("%c", ' ');
            }
        }
        /*
         * Cuando el snake toca una nueva parte del snake se genera otra parte en un lugar aleatorio, etc
         */ 
        if(snake -> posX == posSnakeChunk[0] && snake -> posY == posSnakeChunk[1]){
            posSnakeChunk = printSnakeChunk();
            snake -> sizeSnake += 1;
            addSnake();
        }
        // Salto de fila
        printf("\n");
    }
}

void addSnake(){
    snake -> body = realloc(snake -> body, snake -> sizeSnake);
    snake -> body[(snake -> sizeSnake) - 1] = '*';
}

int* printSnakeChunk(){
    int posX = (rand() % (WIDTH - 2)) + 1;
    int posY = (rand() % (HEIGHT - 2)) + 1;
    
    posSnakeChunk[0] = posX;
    posSnakeChunk[1] = posY;
    

    return posSnakeChunk;
}

int controls(){
    if(kbhit()){
        char c = getch();
        int flag;

        // UP
        if(c == 'w'){
            snake -> posY += - 1;
            flag = 1;
        }
        // DOWN
        else if(c == 's'){
            snake -> posY += + 1;
            flag = 2;
        }
        // LEFT
        else if(c == 'a'){
            snake -> posX += - 1;
            flag = 3;
        }
        //RIGHT
        else if(c == 'd'){
            snake -> posX += + 1;
            flag = 4;
        }
        else if(c == 27){
            exit(EXIT_SUCCESS);
        }
    }
    system("cls");
}