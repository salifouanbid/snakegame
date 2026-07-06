/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
// Define the dimensions of the grid  
 
void drawGrid(snake s) {

    //effacer l'ecran

    system("cls");


// Draw the grid
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
         {
            //boucle pour le serpent
    int estserpent=0;
    int estpomme=0;
    for(int i=0;i < s.length;i++){
        if(s.body[i].x==x && s.body[i].y==y )
        {
            estserpent=1;
            break;
        }
        }
    
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                printf("#");
            } 
            else if(estserpent==1){
                printf("0");
            }
            
            else {
                printf(" ");
            }
        }
        
        printf("\n");
    }
}

    




int main() {
    // Draw the grid
    
    snake serpent;
    serpent.length=3;
    serpent.body[0].x= 15;
    serpent.body[0].y= 10;
    serpent.body[1].x= 14;
    serpent.body[1].y= 10;
    serpent.body[2].x= 13;
    serpent.body[2].y= 10;

    //draw the grid

    drawGrid(serpent);
    printf("\nappuyer sur entrer pour continuer...");
    getchar();

    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "main.h"

void initsnake(void){
    serpent.length = 5;
    serpent.direction = RIGHT;
    serpent.ateapple = 0;
    for(int i = 0; i < serpent.length; i++){
        serpent.body[i].x = 6 - i;
        serpent.body[i].y = 4;
    }
}

int pommesurserpent(void){
    for(int i = 0; i < serpent.length; i++){
        if(serpent.body[i].x == pomme.x && serpent.body[i].y == pomme.y){
            return 1;
        }
    }
    return 0;
}

void putpomme(void){
    do{
        pomme.x = (rand() % (WIDTH - 2)) + 1;
        pomme.y = (rand() % (HEIGHT - 2)) + 1;
    } while(pommesurserpent());
}

void initgame(void){
    srand((unsigned int)time(NULL));
    initsnake();
    putpomme();
    score = 0;
    delai = DELAI_INIT;
    encours = 1;
}

void drawGrid(void) {
    system("cls");
}

int estsurserpent(int x, int y){
    for(int i = 1; i < serpent.length; i++){
        if(serpent.body[i].x == x && serpent.body[i].y == y){
            return 1;
        }
    }
    return 0;
}

void afficherplateau(void){
    drawGrid();
    printf("Score: %d\n", score);
    
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            if(x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1){
                printf("#");
            }
            else if(x == serpent.body[0].x && y == serpent.body[0].y){
                printf("0");
            }
            else if(estsurserpent(x, y)){
                printf("o");
            }
            else if(x == pomme.x && y == pomme.y){
                printf("p");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}

int iseatingapple(int x, int y){
    if(x == pomme.x && y == pomme.y){
        return 1;
    }
    return 0;
}  

void avancerserpent(){
    int futurx = serpent.body[0].x;
    int futury = serpent.body[0].y;

    switch(serpent.direction){
        case UP:    futury--; break;
        case DOWN:  futury++; break;
        case LEFT:  futurx--; break;
        case RIGHT: futurx++; break;
    }

    int mange = iseatingapple(futurx, futury);

    for(int i = serpent.length - 1; i > 0; i--){
        serpent.body[i] = serpent.body[i-1];
    }
    
    if (mange) {
        serpent.length++;
        score++;
        putpomme();
    }
    
    serpent.body[0].x = futurx;
    serpent.body[0].y = futury;
}

void changerdirection(direction d){
    if((serpent.direction == UP && d == DOWN) || 
       (serpent.direction == DOWN && d == UP) || 
       (serpent.direction == LEFT && d == RIGHT) || 
       (serpent.direction == RIGHT && d == LEFT)){
        return;
    }
    serpent.direction = d;
}

void lireclavier(void){
    if (_kbhit()) {
        int ch = _getch();
        switch (ch) {
            case 'w': case 'Z': case 'z': 
                changerdirection(UP);
                break;
            case 's': case 'S':
                changerdirection(DOWN);
                break;
            case 'a': case 'Q': case 'q': 
                changerdirection(LEFT);
                break;
            case 'd': case 'D':
                changerdirection(RIGHT);
                break;
        }
    }
}

void collisionmur(){
    if(serpent.body[0].x <= 0 || serpent.body[0].x >= WIDTH - 1 || 
       serpent.body[0].y <= 0 || serpent.body[0].y >= HEIGHT - 1){
        encours = 0;
    }
}

void collisionserpent(){
    for(int i = 1; i < serpent.length; i++){
        if(serpent.body[0].x == serpent.body[i].x && serpent.body[0].y == serpent.body[i].y){
            encours = 0;
        }
    }
}

void speedup(void){
    static int dernier_score_palier = 0;
    if(score % 5 == 0 && score != 0 && score != dernier_score_palier && delai > DELAI_MIN){
        delai -= 20; 
        if(delai < DELAI_MIN){
            delai = DELAI_MIN;
        }
        dernier_score_palier = score;
    }
}

void gameover(void){
    printf("Game Over!\n");
    printf("Final Score: %d\n", score);
    printf("Press SPACE to replay, or any other key to exit...\n");
    
    int touche = _getch();
    if(touche == 32){ 
        initgame();
        while(encours){
            afficherplateau();
            lireclavier();
            avancerserpent();
            collisionmur();
            collisionserpent();
            speedup();
            Sleep(delai);
        }
        gameover();
    } else {
        exit(0);
    }
}

int main(){
    initgame();
    
    while(encours){
        afficherplateau();
        lireclavier();
        avancerserpent();
        collisionmur();
        collisionserpent();
        speedup();
        Sleep(delai);
    }
    gameover();
    return 0;
}


