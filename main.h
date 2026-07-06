#ifndef MAIN_H
#define MAIN_H


#define WIDTH 30
#define HEIGHT 20
#define MAX_LENGTH 100
#define MAX_POMMES 10
#define DELAI_INIT 200
#define DELAI_MIN 50
typedef struct point
{
    int x;
    int y;
} point;
typedef enum direction{
    UP=0,
    DOWN=1,
    LEFT=2,
    RIGHT=3
} direction;
typedef struct 
{
    point body[100];
    int length;
    direction direction;
    int ateapple;
} snake;

extern snake serpent;
extern point pomme;
extern int score;
extern int delai;
extern int encours;

void initsnake(void);
void putpomme(void);
void initgame(void);
void drawGrid(void);    
void afficherplateau(void);
void avancerserpent(void);
void changerdirection(direction d);
void lireclavier(void);
void collisionmur(void);
void collisionserpent(void);
int estsurserpent(int x,int y);
int pommesurserpent(void);
int iseatingapple(int x,int y);
void speedup(void);
void gameover(void);

#endif // MAIN_H    