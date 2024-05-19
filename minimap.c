#include "minimap.h"
 
void init_maske(SDL_Surface **maske)
{
    *maske = IMG_Load("resourcesMinimap/images/background/backgroundmask/backmaske.png");
    if (*maske == NULL) {
        
        fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

  
}

 
 

 

 
 
 



void initmap(minimap * m) {


m->minimap.image=IMG_Load("resourcesMinimap/images/minimap/minimap.png");
m->minimap.positioninscrenn.x=0;
m->minimap.positioninscrenn.y=0;


m->bonhomme.image=IMG_Load("resourcesMinimap/images/bonhomme/bonhomme.png");
m->bonhomme.positioninscrenn.x=10;
m->bonhomme.positioninscrenn.y=10;

m->animation.image=IMG_Load("resourcesMinimap/images/sprite sheet/animation.png");
m->animation.positioninscrenn.x=350;
m->animation.positioninscrenn.y=60;
m->animation.positionfromimage.x=0;
m->animation.positionfromimage.y=0;
m->animation.positionfromimage.h=47;
m->animation.positionfromimage.w=30;


TTF_Init(),
m->timestarted=SDL_GetTicks();
m->time.font=TTF_OpenFont("resources/fonts/font 1/LLPIXEL3.ttf",50);
m->time.color=(SDL_Color){255,255,255};
m->time.text= TTF_RenderText_Blended(m->time.font,"0",m->time.color);
m->time.postext.x=0;
m->time.postext.y=0;
};
void afficherminimap(minimap m,SDL_Surface *screen) {

SDL_BlitSurface(m.minimap.image,NULL,screen,&m.minimap.positioninscrenn);
SDL_BlitSurface(m.bonhomme.image,NULL,screen,&m.bonhomme.positioninscrenn);
SDL_BlitSurface(m.animation.image,&m.animation.positionfromimage,screen,&m.animation.positioninscrenn);


m.time.font=TTF_OpenFont("resources/fonts/font 1/LLPIXEL3.ttf",50);
m.time.color=(SDL_Color){255,255,255};
 
m.time.postext.x=0;
m.time.postext.y=0;


SDL_BlitSurface(m.time.text,NULL,screen,&m.time.postext);

};
void Liberer (minimap * m){
SDL_FreeSurface(m->minimap.image);
SDL_FreeSurface(m->bonhomme.image);
SDL_FreeSurface(m->animation.image);

};

void MAJMinimap(SDL_Rect posJoueur,  minimap * m, SDL_Rect camera, int redimensionnement){
SDL_Rect posJoueurABS;
posJoueurABS.x =posJoueur.x+camera.x;
posJoueurABS.y =posJoueur.y + camera.y;

m->bonhomme.positioninscrenn.x=posJoueurABS.x*redimensionnement/100;
m->bonhomme.positioninscrenn.y=posJoueurABS.y*redimensionnement/100;

};
 

  
  
  SDL_Color  GetPixel(SDL_Surface *pSurface,int x,int y)

{
SDL_Color color;
Uint32 col=0;

char* pPosition=(char* ) pSurface->pixels;
pPosition+= (pSurface->pitch * y);
pPosition+= (pSurface->format->BytesPerPixel *x);
memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);

SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
return (color); 
}
int collisionPP(Personne *p, SDL_Surface *Masque, Background bp, SDL_Surface *screen) {
    int persowidth = 24;
    int persoheight = 39.4;
    SDL_Color color;
    Uint32 green = SDL_MapRGB(screen->format, 0, 255, 0); 

   
    int x = p->perso.positioninscrenn.x + persowidth + bp.pos2.x;
    int y = p->perso.positioninscrenn.y + persoheight / 2 + bp.pos2.y;
    color = GetPixel(Masque, x, y);
    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tabcollison[0] = 1;
        SDL_Rect pointRect = {x, y, 3, 3}; 
        SDL_FillRect(screen, &pointRect, green);
    } else {
        p->tabcollison[0] = 0;
    }
if (color.r==255&&color.g==0&&color.b==0){
    
    p->tabcollison[4]=1;
} 

 if (color.r==0&&color.g==255&&color.b==0){
      p->tabcollison[5]=1;
}  if (color.r==0&&color.g==30&&color.b==255){
      p->tabcollison[6]=1;
}
  
    int x1 = p->perso.positioninscrenn.x + bp.pos2.x;
    int y1 = p->perso.positioninscrenn.y + persoheight / 2 + bp.pos2.y;
    color = GetPixel(Masque, x1, y1);
    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tabcollison[1] = 1;
        SDL_Rect pointRect = {x1, y1, 3, 3}; 
        SDL_FillRect(screen, &pointRect, green);
    } else {
        p->tabcollison[1] = 0;
    }
if (color.r==255&&color.g==0&&color.b==0){
  
    p->tabcollison[4]=1;
} 

 if (color.r==0&&color.g==255&&color.b==0){
      p->tabcollison[5]=1;
}  if (color.r==0&&color.g==30&&color.b==255){
      p->tabcollison[6]=1;
}

    int x2 = p->perso.positioninscrenn.x + bp.pos2.x + persowidth / 2;
    int y2 = p->perso.positioninscrenn.y + bp.pos2.y;
    color = GetPixel(Masque, x2, y2);
    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tabcollison[2] = 1;
        SDL_Rect pointRect = {x2, y2, 3, 3}; 
        SDL_FillRect(screen, &pointRect, green);
    } else {
        p->tabcollison[2] = 0;
    }
if (color.r==255&&color.g==0&&color.b==0){

    p->tabcollison[4]=1;
} 

 if (color.r==0&&color.g==255&&color.b==0){
      p->tabcollison[5]=1;
} 
 if (color.r==0&&color.g==30&&color.b==255){
      p->tabcollison[6]=1;
}    int x3 = p->perso.positioninscrenn.x + bp.pos2.x + persowidth / 2;
    int y3 = p->perso.positioninscrenn.y + bp.pos2.y + persoheight;
    color = GetPixel(Masque, x3, y3);
    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tabcollison[3] = 1;
        SDL_Rect pointRect = {x3, y3, 3, 3}; 
        SDL_FillRect(screen, &pointRect, green);
    } else {
        p->tabcollison[3] = 0;
    }
if (color.r==255&&color.g==0&&color.b==0){
 
    p->tabcollison[4]=1;
} 

 if (color.r==0&&color.g==255&&color.b==0){
      p->tabcollison[5]=1;
}
 if (color.r==0&&color.g==30&&color.b==255){
      p->tabcollison[6]=1;
}
    
    SDL_Flip(screen);

 

    return 0;
}


void animerMinimap(minimap *m) {
if(m->animation.positionfromimage.x>m->animation.image->w-m->animation.positionfromimage.w){
m->animation.positionfromimage.x=0;

}else {

m->animation.positionfromimage.x+=m->animation.positionfromimage.w ;

}






};
void calculnewtime(minimap *m){
char time[12];
Uint32 timelapsed =SDL_GetTicks()-m->timestarted;
sprintf(time,"%d",timelapsed/1000);
m->time.text= TTF_RenderText_Blended(m->time.font,time,m->time.color);
}; 
