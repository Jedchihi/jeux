#include <SDL/SDL.h>
#include "background.h"
#include <SDL/SDL_image.h>


void initBack(Background * b)
{
		   b->scrollright=0;
     b-> scrollleft=0;
     b-> scrollup=0;
     b-> scrollldown=0;
 b->img= IMG_Load("src/maps/map_lv1.png");
 	if(b->img == NULL) {
 		printf("erreur unable to load: %s\n",SDL_GetError());
 		return;
 }
 	b->pos1.x=0;
 	b->pos1.y=0;
 	b->pos2.x=0;
 	b->pos2.y=0;
 	b->pos2.w=1200;
 	b->pos2.h=631;
 
  
    
 


 b->bg=b->img;


}

void aficherBack(Background b, SDL_Surface * screen)
{
SDL_BlitSurface(b.bg,&b.pos2,screen,&b.pos1);
}

void liberer(Background a)
{
SDL_FreeSurface(a.img);
}

void scrolling(Background *b, int direction, int pas)
{ 
     // Move the background rectangle in the specified direction
    switch (direction)
    {

    case 0: // Scroll right
        b->pos2.x += pas;
 
        int scrollLimit = b->img->w - 1200;

        if (b->pos2.x > scrollLimit)
        {
            b->pos2.x = scrollLimit;
        }

        break;

    case 1: // Scroll left
        b->pos2.x -= pas;
        if (b->pos2.x < 0)
        {
            b->pos2.x = 0;
        }
        break;

    case 2: // Scroll up
        b->pos2.y -= pas;
        if (b->pos2.y < -100)
        {
            b->pos2.y = -100;
        }
        break;
    case 3: // Scroll down
        b->pos2.y += pas;
        if (b->pos2.y > (800 -b->img->h))
        {
            b->pos2.y = 800 - b->img->h;
        }
        break;
    }
}

void animerBackground( Background * e)
{
 

 
}

void sauvegarder( int score, char nomjoueur[], char scores[])
{
FILE* f=NULL;
f=fopen(scores,"a");
if(f!=NULL)
    {
  fprintf (f,"%s %d\n",nomjoueur,score);

    fclose(f);
}
}
void meilleur( char scores[], int *score, char nomjoueur[])
{
   FILE* f=NULL;
   char player[20] ;
   int mc,s;

f=fopen(scores,"r");
if (f!=NULL)
{
mc=0;
while(fscanf(f,"%s %d\n",player,&s)!=EOF)
{
    if(mc<s)
   {
    mc=s;
    strcpy(nomjoueur,player);
   }
*score=mc;
}
}

fclose(f);
}
void initVie(image *img)
{
 	img->img = IMG_Load("src/coeur/vie.png");
 		if (img->img == NULL) {
 		printf("erreur unable to load: %s\n",SDL_GetError());
 			return;
 		}
 	img->pos1.x=300;
 	img->pos1.y=0;
 	img->pos1.h=49;
 	img->pos1.w=300;
 	img->pos2.x=0;
 	img->pos2.y=0;
 	img->pos2.h=img->pos1.h;
 	img->pos2.w=img->pos1.w/5;
 }
void afficheVie(image img, SDL_Surface * screen)
{
	SDL_BlitSurface(img.img,&img.pos2,screen,&img.pos1); 
}

void liberer1(image a)
{
	SDL_FreeSurface(a.img);
}
