#include"minimap.h"
#include"tictactoe.h"
#include "enigme.h"
#include "entity.h"
#include <stdbool.h>
 void runGameLoop(Enigme *e, SDL_Surface *screen, SDL_Surface *horloge[]);
int main() {



    Enigme e;
    SDL_Color textColor = {255, 255, 255};
    char reponse[1024] = {0};
    char question[1024] = {0};
    char bonnes_reponses[1024] = {0};
    FILE *fp = fopen("src_enigme/question_index.txt", "r+");
    SDL_Surface *horloge[10];

SDL_Surface* screen ;

int rest;
rest=0;
int quitter;
SDL_Event event;
Personne p;
uint32_t tprev,tprev5;
Uint32 t_prev,t_prev2;
int posinit;
float dt;
minimap m;
int mo=0;

	Background background;
	int pasavancementH = 0;
	int pasavancementV = 0;
	int pasavancement = 0;
	int direction = 0;
	image img;
	Uint32 t_prev1;
	int ii = 0;
	texte t, t1;
	Uint32 score = 0;
	char zz[10];
	char scores[30] = "src/scores.txt";
	int sp = 0;
	char nom[20] = "louai";
	char message[20] = "looooool", ch[20];
	char nj[20];

		int repitition_enigme=0 ;
		xo t_enigme;
	rotozoom z_enigme;
	background_engime back_enigme;
	image_enigme im_enigme;
	Mix_Music *son_enigme;
	Mix_Chunk *rebh_enigme;
	Mix_Chunk *khsara_engime;










SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO);
screen= SDL_SetVideoMode(1200, 631, 32, SDL_RESIZABLE|SDL_HWSURFACE);
quitter=1;
posinit=400;

init_maske(&background.masque);
enemie en;
bonus b;
initennemi(&en, &b);
initPerso(&p);
initmap(&m);

	TTF_Init();
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}
	initTexte(&t, 0, 0, 250, 250, 250, "src/font/Roboto-BoldItalic.ttf", 30);
	initTexte(&t1, 90, 0, 250, 250, 250, "src/font/Roboto-BoldItalic.ttf", 30);
	initVie(&img);
	atexit(SDL_Quit);
	background.n = 0;
	initBack(&background);
	InitialiserBackground(&back_enigme);
	InitialiserXO(&t_enigme);
	Init_rotozoom(&z_enigme);
	son_enigme=Mix_LoadMUS("song/son.mp3");
	Mix_PlayMusic(son_enigme,-1);
	rebh_enigme=Mix_LoadWAV("song/gagner.wav");
	khsara_engime=Mix_LoadWAV("song/bankeji.wav");

  int enaween=0;
  int onetime=1;
  int onetime2=1;

    InitEnigme(&e);
    e.questionIndex = 0;
    if (fp)
    {
        fscanf(fp, "%d", &(e.questionIndex));
        fclose(fp);
    }

    e.questionIndex = (e.questionIndex + 1) % e.totalQuestions;

    fp = fopen("src_enigme/question_index.txt", "w");
    if (fp)
    {
        fprintf(fp, "%d", e.questionIndex);
        fclose(fp);
    }

    inithorloge(horloge);
    genererEnigme(&e, reponse, question, bonnes_reponses, textColor, e.questionIndex);









while(quitter){
  if (enaween==0 ) {
    if(rest){
             enaween=0;
        onetime=0;
        event.type=0;
		   background.scrollright=0;
    background.scrollleft=0;
    background. scrollup=0;
     background.scrollldown=0;
     rest=0;
    }
t_prev=SDL_GetTicks();
		 aficherBack(background, screen);
afficherPerso(p,screen);
afficherennemi(&en, &b, screen);
afficherminimap(m,screen);
		animerBackground(&background);

		afficheVie(img, screen);
		displaytexte(t, screen, "Score: ");
		displaytexte(t1, screen, zz);



SDL_PollEvent(&event);

switch(event.type){

  case SDL_QUIT:
  quitter=0;
  break;



  case SDL_KEYDOWN:
switch(event.key.keysym.sym) {


case SDLK_UP:
background.scrollup = 1;
if(p.up==0){
p.up=1;
p.velocityX=0;
p.velocityY=-80;
}
break;
case SDLK_DOWN:
 background.scrollldown = 1;
break;
case SDLK_RIGHT:
//background.scrollright = 1;
p.deplacement=1;
p.direction=0;
break;
case SDLK_LEFT:
//background.scrollleft = 1;
p.deplacement=1;
p.direction=1;
break;
case SDLK_SPACE:
if(p.up==0){
p.up=1;
p.velocityX=60;
p.velocityY=-100;
}
break;
}
break;

case SDL_KEYUP:
switch(event.key.keysym.sym) {
case SDLK_RIGHT:
background.scrollright = 0;
p.deplacement=0;
break;
case SDLK_LEFT:
background.scrollleft = 0;
p.deplacement=0;
break;
			case SDLK_UP:

				background.scrollup = 0;
				break;
			case SDLK_DOWN:
				background.scrollldown = 0;

				break;
}
break;

}


p.acceleration-=0.001;
if(p.etatA==1){p.acceleration+=0.005;}
else if(p.etatD==1){p.acceleration-=0.01;}

if(p.acceleration<0){
 p.acceleration=0;
}
if(p.acceleration>0.2) {
 p.acceleration=0.2;
}
if(p.deplacement==1){
  p.Vscore+=1;
  p.vitesse=0.5;
p.acceleration+=0.002;

}else if(p.deplacement==0){
   p.vitesse=0;
}
if(p.up==0){

movePerso(&p,&background);
}
deplacerIA(&en, p.perso.positioninscrenn);

if(p.deplacement==1||p.up==1) {
    if(SDL_GetTicks()-tprev>80) {
animerPerso(&p);

tprev=SDL_GetTicks();
  }
animerennemi(&en);
}
saut(&p,dt,posinit,&background);

//------updateminimap
MAJMinimap(p.perso.positioninscrenn,&m, background.pos2,20);
collisionPP(&p,background.masque,background,screen);
if(p.tabcollison[3]!=1) {
  p.perso.positioninscrenn.y+=1;
}

animerMinimap(&m);
calculnewtime(&m);


		if (SDL_GetTicks() - t_prev1 > 20)
		{


			if (background.scrollright == 1)
			{
				scrolling(&background, 0, 5);
			}
			else if (background.scrollleft == 1)
			{
				scrolling(&background, 1, 5);
			}

			if (background.scrollup == 1)
			{
				//scrolling(&background, 2, 5);
			}
			else if (background.scrollldown == 1)
			{
				//scrolling(&background, 3, 5);
			}
			t_prev1 = SDL_GetTicks();

		}
		ii++;
		if (ii % 100 == 0)
		{
			img.pos2.x += 62;
			if (img.pos2.x >= 300)
				img.pos2.x = 0;
		}
		sprintf(zz, "%d", sp);
		score += SDL_GetTicks() / 1000;

            if (p.tabcollison[4] == 1 && onetime == 1)
      {

        enaween = 1;
      }
                  if (p.tabcollison[5] == 1 && onetime2 == 1)
      {

        enaween = 2;
      }
p.dt=SDL_GetTicks()-t_prev;
dt=(SDL_GetTicks()-t_prev)/100.0;
}
else
if (enaween==1&&onetime==1)
 {

	            if (SDL_GetTicks() - tprev5 > 20){


	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));


			AfficherBackground(screen , back_enigme);
			AfficherXO( screen , t_enigme );
			AfficheNavigation(screen , t_enigme);
			AfficherRoto(screen,&z_enigme);
			    tprev5=SDL_GetTicks();
      }
      		if(z_enigme.t == 1 ){
            if (SDL_GetTicks() - t_prev2 > 2000){
mo++;
      t_prev2=SDL_GetTicks();
      }
		}

			Annimation(&back_enigme);
			if(Atilganger(t_enigme.tab) == 1 || egalite(t_enigme.tab) != 0)
			{
				z_enigme.t=Atilganger(t_enigme.tab);
				repitition_enigme=1;
				if(repitition_enigme==1)
				{
					Mix_PlayChannel( -1,rebh_enigme,0);
					repitition_enigme=0;
				}
				clearTable(&t_enigme);
			}
			else if(Atilganger(t_enigme.tab) == 2 || egalite(t_enigme.tab) != 0)
			{
				z_enigme.t=Atilganger(t_enigme.tab);
				repitition_enigme=1;
				if(repitition_enigme==1)
				{
					Mix_PlayChannel( -1,khsara_engime,0);
					repitition_enigme=0;
				}
				clearTable(&t_enigme);
			}
			while( SDL_PollEvent (&event) ){

				switch(event.type){

					case SDL_QUIT:
						quitter = 0;
					break;
					case SDL_MOUSEBUTTONUP:
						for(int i=0; i<3;i++){
							for(int j=0;j<3;j++){
								if(event.motion.x > t_enigme.pos[i][j].x && event.motion.x < t_enigme.pos[i][j].x + t_enigme.pos[i][j].w
								&&event.motion.y > t_enigme.pos[i][j].y && event.motion.y < t_enigme.pos[i][j].y + t_enigme.pos[i][j].h ){

									if(t_enigme.tab[i][j] == 0){
										if(t_enigme.n==0){
											t_enigme.tab[i][j] = 1;
											t_enigme.n=1;

										}
									}

								}
							}
						}
						if(t_enigme.n==1){
							ia(&t_enigme);
							t_enigme.n=0;

						}

					break;
					case SDL_KEYDOWN:

						if(event.key.keysym.sym == SDLK_RIGHT ){

							t_enigme.selection++;
							if( t_enigme.selection == 9 ){
								t_enigme.selection = 0;
							}
						}
						else if(event.key.keysym.sym == SDLK_LEFT ){

							t_enigme.selection--;
							if( t_enigme.selection <= -1 ){
								t_enigme.selection = 8;
							}
						}
						else if(event.key.keysym.sym == SDLK_DOWN ){

							t_enigme.selection += 3 ;
							if( t_enigme.selection == 9   ){
								t_enigme.selection -= 9 ;
							}
						}
						else if(event.key.keysym.sym == SDLK_UP ){

							t_enigme.selection -= 3 ;
							if( t_enigme.selection <= -1   ){
								t_enigme.selection += 9 ;
							}
						}
					else if(event.key.keysym.sym == SDLK_RETURN){

						if(t_enigme.selection >= 0 && t_enigme.selection <= 2 ){
							if( t_enigme.tab[0][t_enigme.selection] == 0 ){
								t_enigme.tab[0][t_enigme.selection] = t_enigme.n+1;
								if(t_enigme.n==1){
									t_enigme.n=0;
								}
								else t_enigme.n=1;
							}
							z_enigme.t=Atilganger(t_enigme.tab);
						}
						else if(t_enigme.selection >= 3 && t_enigme.selection <= 5){

							if( t_enigme.tab[1][t_enigme.selection -3 ] == 0 ){
								t_enigme.tab[1][t_enigme.selection - 3 ] = t_enigme.n+1;
								if(t_enigme.n==1){
									t_enigme.n=0;
								}
								else t_enigme.n=1;
							}
							z_enigme.t=Atilganger(t_enigme.tab);

						}
						else {
							if( t_enigme.tab[2][t_enigme.selection - 6 ] == 0 ){
								t_enigme.tab[2][t_enigme.selection - 6 ] = t_enigme.n+1;
								if(t_enigme.n==1){
									t_enigme.n=0;
								}
								else t_enigme.n=1;
							}
							z_enigme.t=Atilganger(t_enigme.tab);
						}
					}



					break;

				}
				SDL_Flip(screen);

			}




    if(mo==3) {
       enaween=0;
 onetime=0;
 event.type=0;
		   background.scrollright=0;
    background.scrollleft=0;
    background. scrollup=0;
     background.scrollldown=0;
     rest=1;
    }

}else if (enaween==2&&onetime2==1){
    afficherEnigme(&e, screen);


    runGameLoop(&e, screen, horloge);
       enaween=0;
 onetime2=0;
 event.type=0;
		   background.scrollright=0;
    background.scrollleft=0;
    background. scrollup=0;
     background.scrollldown=0;
     rest=1;

}

SDL_Flip(screen);


}


      freeEnigme(&e);

	sauvegarder(sp, nom, scores);
	meilleur(scores, &sp, nj);
	printf("  ******************************\n");
	printf("the best score %d belongs to %s\n", sp, nj);
	printf("  ******************************\n");
	liberer(background);

	freeTexte(t);
	freeTexte(t1);
	TTF_CloseFont(t.font);
	TTF_CloseFont(t1.font);
	liberer1(img);


SDL_FreeSurface( background.masque);
Liberer(&m);
Mix_FreeMusic(son_enigme);
SDL_Quit();






}
void runGameLoop(Enigme *e, SDL_Surface *screen, SDL_Surface *horloge[])
{

    bool running = true;
    int rep = 0;
    SDL_Event event;

    Uint32 lastAnimationTime = SDL_GetTicks();

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastAnimationTime > 100)
        {
            lastAnimationTime = currentTime;
            animateHorloge(horloge, screen, 10);
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    rep = 0;
                    checkAnswer(e, rep, screen);
                    running=0;
                    break;
                case SDLK_b:
                    rep = 1;
                    checkAnswer(e, rep, screen);
                    running=0;
                    break;
                case SDLK_c:
                    rep = 2;
                    checkAnswer(e, rep, screen);
                    running=0;
                    break;
                case SDLK_SPACE:
                    running = false;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.x > 100 && event.button.y > 300 && event.button.x < 925 && event.button.y < 415)
                {
                    rep = 0;
                    checkAnswer(e, rep, screen);
                    running=0;
                    break;
                }
                else if (event.button.x > 100 && event.button.y > 430 && event.button.x < 925 && event.button.y < 540)
                {
                    rep = 1;
                    checkAnswer(e, rep, screen);
                    running=0;
                    break;
                }
                else if (event.button.x > 100 && event.button.y > 560 && event.button.x < 925 && event.button.y < 675)
                {
                    rep = 2;
                    checkAnswer(e, rep, screen);
                    running=0;
                    break;
                }

                break;
            }
        }

        SDL_Delay(10);
    }
}

