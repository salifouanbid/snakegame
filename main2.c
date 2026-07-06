#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "main.h"
point pomme;
snake serpent;
int score;
int delai;   
int encours;

void initsnake(void){
    serpent.length=5;
    serpent.direction=RIGHT;
    serpent.ateapple=0;
    for(int i=0;i<serpent.length;i++){
        serpent.body[i].x=6-i;
        serpent.body[i].y=4;
    }
}

int pommesurserpent(void){
    for(int i=0;i<serpent.length;i++){
        if(serpent.body[i].x==pomme.x && serpent.body[i].y==pomme.y){
            return 1;
        }
    }
    return 0;
}
void putpomme(void){
    do{
        pomme.x=rand()%(WIDTH);
        pomme.y=rand()%(HEIGHT);
    }while(pommesurserpent());
}

void initgame(void){
    system("cls");
    initsnake();
    putpomme();
    score=0;
    delai=DELAI_INIT;
    encours=1;
    srand((unsigned int)time(NULL));
}


void drawGrid(void) {

    COORD coord={0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void cachercurseur(void){
    HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize=1;
    GetConsoleCursorInfo(out,&cursorInfo);
    cursorInfo.bVisible=FALSE;
    SetConsoleCursorInfo(out,&cursorInfo);
}

int estsurserpent(int x,int y){
    for(int i=1;i<serpent.length;i++){
        if(serpent.body[i].x==x && serpent.body[i].y==y){
            return 1;
        }
    }
    return 0;
}


void afficherplateau(void){
    drawGrid();
    printf("Score: %d\n",score);
    /* exemple de fonction bon c'est pas meme chose hum mais bon ca y ressemble
    for(int y=0;y<HEIGHT;y++){
        for(int x=0;x<WIDTH;x++){
            if(x==0 || x==WIDTH-1 || y==0 || y==HEIGHT-1){
                printf("#");
            }
            else if(estsurserpent(x,y)){
                printf("0");
            }
            else if(pomme.x==x && pomme.y==y){
                printf("p");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }*/
   for(int y=0;y<HEIGHT;y++){
        for(int x=0;x<WIDTH;x++){
            if(x==0 || x==WIDTH-1 || y==0 || y==HEIGHT-1){
                printf("#");
            }
            else if(x==serpent.body[0].x && y==serpent.body[0].y){
                printf("\033[1;32m0\033[0m"); // Tête du serpent en vert]");
            }
            else if(estsurserpent(x,y)){
                printf("\033[1;31mo\033[0m"); // Corps du serpent en rouge
            }
            else if(pomme.x==x && pomme.y==y){
                printf("\033[1;33mp\033[0m"); // Pomme en jaune
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
   }
void avancerserpent(){
    int futurx=serpent.body[0].x;
    int futury=serpent.body[0].y;

    switch(serpent.direction){
        case UP:
            futury--;
            break;
        case DOWN:
            futury++;
            break;
        case LEFT:
            futurx--;
            break;
        case RIGHT:
            futurx++;
            break;
    }
    if(iseatingapple(futurx,futury)){
        serpent.length++;
        score++;
        putpomme();
        
    }
    
    for(int i=serpent.length-1;i>0;i--){
        serpent.body[i]=serpent.body[i-1];
    }
    serpent.body[0].x=futurx;
    serpent.body[0].y=futury;
    /*if(serpent.body[0].x==pomme.x && serpent.body[0].y==pomme.y){
    serpent.length++;
    }*/
}
void changerdirection(direction d){
    if((serpent.direction==UP && d==DOWN) || (serpent.direction==DOWN && d==UP) || (serpent.direction==LEFT && d==RIGHT) || (serpent.direction==RIGHT && d==LEFT)){
        return;
    }
    serpent.direction=d;
}

/*Je veux enclencher la lecture du clavier
void lireclavier(void){
if (_kbhit()) {
    int ch = _getch();
    switch (ch) {
        case 'w':
            changerdirection(UP);
            break;
        case 's':
            changerdirection(DOWN);
            break;
        case 'a':
            changerdirection(LEFT);
            break;
        case 'd':
            changerdirection(RIGHT);
            break;
    }
}
}*/void lireclavier(void){
    if (_kbhit()) {
        int ch = _getch();
        
        // Si ch vaut 0 ou 224, c'est qu'une touche spéciale (comme une flèche) a été pressée
        if (ch == 0 || ch == 224) {
            ch = _getch(); // On lit le second code pour savoir quelle flèche c'est
            
            switch (ch) {
                case 72: // Code de la flèche HAUT
                    changerdirection(UP);
                    break;
                case 80: // Code de la flèche BAS
                    changerdirection(DOWN);
                    break;
                case 75: // Code de la flèche GAUCHE
                    changerdirection(LEFT);
                    break;
                case 77: // Code de la flèche DROITE
                    changerdirection(RIGHT);
                    break;
            }
        }
    }
}

void collisionmur(){
    if(serpent.body[0].x<0 || serpent.body[0].x>=WIDTH || serpent.body[0].y<0 || serpent.body[0].y>=HEIGHT){
        encours=0;
    }
    
}
void collisionserpent(){
    for(int i=1;i<serpent.length;i++){
        if(serpent.body[0].x==serpent.body[i].x && serpent.body[0].y==serpent.body[i].y){
            encours=0;
        }
    }
}

/*pomme*/
int iseatingapple(int x,int y){
        if(x==pomme.x && y==pomme.y){
            return 1;
        }
        return 0;
    }  

void speedup(void){
    if(score%5==0 && score!=0 && delai>DELAI_MIN){
        delai-=20;
        if(delai<DELAI_MIN){
            delai=DELAI_MIN;
        }
    }
}

void gameover(void){
    printf("Game Over!\n");
    printf("Final Score: %d\n", score);
    printf("Press any key to exit...and replay if you want!\n");
   int touche = _getch();
   if(touche==32){
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
       encours=1;
       delai=DELAI_INIT;
       putpomme();
       gameover();
     }
     
     else{
         exit(0);
     }
}
/*
void replay(void){
    printf("Do you want to play again? (y/n): ");
    char choice = _getch();
    if(choice=='y' || choice=='Y'){
        initgame();
        encours=1;
    }
    else{
        exit(0);
    }
}*/

int main(){
    
    initgame();
    cachercurseur();
    putpomme();
    system("cls");
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
