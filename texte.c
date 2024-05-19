#include <SDL/SDL.h>
#include "texte.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
void initTexte(texte *t,int x,int y,int r,int g,int b,char name[], int s)
{
	t->position.x=x;
	t->position.y=y;
	
	t->texteCoulor.r=r;
	t->texteCoulor.g=g;
	t->texteCoulor.b=b;
	
	t->font=TTF_OpenFont(name,s);
}

void freeTexte1(texte t,texte t1)
{
		SDL_FreeSurface(t.surfaceTexte);
		SDL_FreeSurface(t1.surfaceTexte);
}

void freeTexte(texte t)
{
		SDL_FreeSurface(t.surfaceTexte);
}

void displaytexte(texte t,SDL_Surface *screen,char name[])
{
	t.surfaceTexte=TTF_RenderText_Blended(t.font,name,t.texteCoulor);
	SDL_BlitSurface(t.surfaceTexte,NULL,screen,&t.position);
}
void inittext (text *t)
{
t->pos.x=0;
t->textcolor.r=250;
t->textcolor.g=250;
t->textcolor.b=250;
t->font=TTF_OpenFont("OpenSans-Bold.ttf",30);
}
void inittext2 (text *t)
{
t->pos.x=1800;
t->pos.y=50;
t->textcolor.r=250;
t->textcolor.g=250;
t->textcolor.b=250;
t->font=TTF_OpenFont("Roboto-BoldItalic.ttf",30);
}

void freetext(text t)
{
SDL_FreeSurface(t.surfacetext);
}
void displaytext(text t,text t2,SDL_Surface *screen ,char message[] )
{
t.surfacetext=TTF_RenderText_Solid(t.font,"Time:",t.textcolor);
t2.surfacetext=TTF_RenderText_Solid(t2.font,message,t2.textcolor);
SDL_BlitSurface(t.surfacetext,NULL,screen,&t.pos);
SDL_BlitSurface(t2.surfacetext,NULL,screen,&t2.pos);
}
