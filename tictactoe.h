#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
typedef struct
{
	SDL_Surface *img[12];
	SDL_Rect pos;
	int nbr;
	int index;
}background_engime;
typedef struct
{
	int x,y,w,h;	
}position;

typedef struct 
{
	SDL_Surface *img;
	SDL_Rect pos;
}image_enigme;

typedef struct
{
	SDL_Surface *img[2];
	SDL_Rect pos[3][3];
	int tab[3][3];
	int n;
	int selection;
}xo;
typedef struct
{
	SDL_Surface *txt;
	char ch[20];
	SDL_Rect posText;
	SDL_Color couleur;
	TTF_Font *police;
}text_enigme;
typedef struct
{
	SDL_Surface *zoom[10];
	SDL_Surface *rotation[10];
	text_enigme goodjob;
	text_enigme hardluck;
	int t,d,r;
}rotozoom;

void InitialiserBackground(background_engime *b);
void AfficherBackground(SDL_Surface *screen , background_engime b);
void Annimation(background_engime *b);
void InitiliserTable(image_enigme *im);
void AfficherTable(SDL_Surface *screen , image_enigme im);
void LibererTous(background_engime *b,image_enigme *im);

void ia(xo *t);
int egalite(int tab[3][3]);
void clearTable(xo *t);
void InitialiserXO(xo *t);
void AfficherXO(SDL_Surface *screen , xo t);
void AfficheNavigation(SDL_Surface *screen , xo t);
int Atilganger(int tab[3][3]);

void Init_Good(text_enigme *good);
void Init_Hard(text_enigme *hard);
void Init_rotozoom(rotozoom *zoom);
void AfficherRoto(SDL_Surface *screen , rotozoom *z);
 



#endif
