#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
#include "texte.h"
typedef struct struct_img {
SDL_Surface* image;
SDL_Rect positioninscrenn;
SDL_Rect positionfromimage;
}struct_img;
typedef struct struct_text{
 TTF_Font *font;
 SDL_Color color;
 SDL_Surface* text;
 SDL_Rect postext;
}struct_text;
typedef struct Personne
{
struct_img perso;
struct_img coeur;
struct_text score;
int nbcoeur;
int Vscore;
int direction;
int deplacement;
double vitesse,acceleration;
int etatA,etatD;
Uint32 dt;
int up;
int velocityY;
int velocityX;
int groundY;
 int tabcollison[7];
}Personne;
 

void init_image2(struct_img *Background);






void init(Personne *p,int numperso);
  void initPerso(Personne *p);
  void afficherPerso(Personne p,SDL_Surface *screen);
 
void animerPerso(Personne *p);

void movePerso(Personne *p,Background *bp);
void saut(Personne *P,float dt, int possol,Background *bp) ;
//-----------------lot functions
