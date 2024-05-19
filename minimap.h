#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
 #include"perso.h"
 
 
typedef struct minimap{
   struct_img minimap;
   struct_img bonhomme ;
   struct_img animation;
   struct_text time ;
   Uint32 timestarted;
}minimap;


 



 





void initmap(minimap * m);
void afficherminimap(minimap m,SDL_Surface *screen);
void Liberer (minimap * m);
void MAJMinimap(SDL_Rect posJoueur,  minimap * m, SDL_Rect camera, int redimensionnement);
void sauvgarder(Personne p,Background b,char *nomfichier);
void charger(Personne *p,Background *b,char *nomfichier);
SDL_Color  GetPixel(SDL_Surface *pSurface,int x,int y);
int collisionPP(Personne *p, SDL_Surface *Masque, Background bp, SDL_Surface *screen) ;
void init_maske(SDL_Surface **maske);
void animerMinimap(minimap *m);
void calculnewtime(minimap *m);

