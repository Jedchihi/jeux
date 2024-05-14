


#include "entity.h"
#include "math.h"


void initennemi(enemie*e,bonus*b) {

    b->bonus_sprite = IMG_Load("image/heart.png");
    b->pos.x = 300; 
    b->pos.y = 300;
 
    e->spritesheet=IMG_Load("image/ennemi_spr.png");
    e->frame=0;
    e->direction=0; 
    e->pos.x=0;
    e->pos.y=0;
    e->posframe.x=0;
    e->posframe.y=0;
    e->posframe.h=100;
    e->posframe.w=100;
    e->posmax.x=1000;
    e->posmin.x=0;

}




void afficherennemi(enemie *e,bonus *b, SDL_Surface * screen) {
   if (e->pos.x>0)
        SDL_BlitSurface(e->spritesheet,&e->posframe,screen,&e->pos);

   if (b->bonus_sprite != NULL) {
       SDL_BlitSurface(b->bonus_sprite,NULL,screen,&b->pos);
   } 
        

   
}

void animerennemi( enemie * e) {
    e->posframe.y = e->direction * 100 ; // e->posframe.y = e->direction * e->posframe.h
    e->posframe.x = e->posframe.x + 100;// e->posframe.x = e->posframe.x + e->posframe.w
    if (e->posframe.x==400)
    {
        e->posframe.x=0;
    }
    
} 


void deplacer( enemie * e)  {
    if (e->direction==0)
    {
        e->pos.x += 5;
    }else if (e->direction==1)
    {
        e->pos.x -= 5;
    }

    if (e->pos.x > e->posmax.x)
    {
        e->direction=1;
    }
    if (e->pos.x < e->posmin.x)
    {
        e->direction=0;
    }   
}


int collision(SDL_Rect E, SDL_Rect p) {
  int collision,px,py;
  px=p.x+100;
  py=p.y+120;
  if (((px + p.w) < E.x) || (px > (E.x + E.w)) || ((py + p.h) < E.y) || (py > (E.y + E.h))) {
    collision = 0;
  } else {
    collision = 1;
  }

  return collision;
}

int collisontri(SDL_Rect b, SDL_Rect p){
  int collisiontri, px,py,xb,yb,rb,rp,xp,xy,d,dd,nbr;
	xb=b.x+b.w/2;
	yb=b.y+b.h/2;
	if (b.w<b.h){
	   rb=b.w/2; 
	} else{
	 rb=b.h/2;}
	px=p.x+100;
        py=p.y+120;
	xp=px+p.w/2;
	xy=py+p.h/2;
	if(p.w<p.h){
	  rp=p.w/2;
	} else {
	rp=p.h/2;}
	nbr=(xp-xb)*(xp-xb)+(xp-xb)*(xp-xb);
	d=sqrt(nbr);
	dd=rb+rp;
	if (d<=dd){
	collisiontri=1;
	} else {
	collisiontri=0;
	}
    return collisiontri; 
}
	


void deplacerIA(enemie * E, SDL_Rect posPerso) {
  if (((E -> pos.x - posPerso.x) < 200) && ((E -> pos.x - posPerso.x) > 80))  
   {
    E -> direction = 1; 
    E -> pos.x -= 8;
  } 
  else if (((E -> pos.x - posPerso.x) < -80) && ((E -> pos.x - posPerso.x) > -400))
   {
    E -> direction = 0; 
    E -> pos.x += 8;
  } 
  else if (((E -> pos.x - posPerso.x) <= 80) && ((E -> pos.x - posPerso.x) >= 0)) 
  {
    E -> direction = 3;
  } 
  else if (((E -> pos.x - posPerso.x) <= 0) && ((E -> pos.x - posPerso.x) >= -80)) 
  {
    E -> direction = 2;
  }
  else deplacer(E);

}

void scrolling_enemie(enemie *E,int direction,int pasAvancement){
  if (direction==1)
	{
		 E->pos.x += pasAvancement;
     E->posmin.x += pasAvancement;
     E->posmax.x += pasAvancement;
	}else if (direction==0)
	{
		E->pos.x -= pasAvancement;
    E->posmin.x -= pasAvancement;
    E->posmax.x -= pasAvancement;
	}
}
