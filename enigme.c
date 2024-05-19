#include "enigme.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL_rotozoom.h>
void InitEnigme(Enigme *e) {
    TTF_Init();
    e->background = IMG_Load("src_enigme/BACKGROUND.jpg");

    SDL_Color textColor = {255, 255, 255};
    e->questionFont = TTF_OpenFont("src_enigme/clerk.ttf", 45);
    e->answerFont = TTF_OpenFont("src_enigme/pepsi.ttf", 30);

    e->posQ.x = 120; e->posQ.y = 175;   
  
    e->questionIndex = 0;     
    e->totalQuestions = 3;   

	e->answerSurfaces[0]= TTF_RenderText_Blended (e->answerFont,e->r1,textColor);
        e->posReponses[0].x = 120;  
        e->posReponses[0].y = 340;  
    

	e->answerSurfaces[1]= TTF_RenderText_Blended (e->answerFont,e->r2,textColor);
        
	e->posReponses[1].x = 120;  
        e->posReponses[1].y = 470;  
    

	e->answerSurfaces[2]= TTF_RenderText_Blended (e->answerFont,e->r3,textColor);

	e->posReponses[2].x = 120;  
        e->posReponses[2].y = 600;  
      	
   
}

void afficherEnigme(Enigme *e, SDL_Surface *screen) {
        
	SDL_BlitSurface(e->background, NULL, screen, NULL);
        SDL_BlitSurface(e->questionSurface, NULL, screen, &e->posQ);
	SDL_BlitSurface(e->answerSurfaces[0],NULL,screen,&(e->posReponses[0]));
        SDL_BlitSurface(e->answerSurfaces[1],NULL,screen,&(e->posReponses[1]));
        SDL_BlitSurface(e->answerSurfaces[2],NULL,screen,&(e->posReponses[2]));

    SDL_Flip(screen); 
}



void genererEnigme(Enigme *e, char *reponse, char *question, char *bonnes_reponses, SDL_Color color, int questionIndex) {
	
    FILE *fq = fopen("src_enigme/question.txt", "r");
    FILE *fa = fopen("src_enigme/reponse.txt", "r");
    FILE *fb = fopen("src_enigme/bonnes_reponses.txt", "r");

    if (!fq || !fa || !fb) {
        fprintf(stderr, "Erreur d'ouverture des fichiers de données\n");
        if (fq) fclose(fq);
        if (fa) fclose(fa);
        if (fb) fclose(fb);
        return;
    }

    int currentLine = 0;
    while (fgets(question, 1024, fq) && fgets(reponse, 1024, fa) && fgets(bonnes_reponses, 1024, fb)) {
        if (currentLine == questionIndex) {
            question[strcspn(question, "\n")] = 0; 
            reponse[strcspn(reponse, "\n")] = 0;
            bonnes_reponses[strcspn(bonnes_reponses, "\n")] = 0;
            
            e->questionSurface = TTF_RenderText_Blended(e->questionFont, question, color);
            e->correctAnswerIndices[currentLine] = atoi(bonnes_reponses); 
          
            char *ptr = strtok(reponse, "|");
            int idx = 0;
            while (ptr && idx < 3) {  
                e->answerSurfaces[idx] = TTF_RenderText_Blended(e->answerFont, ptr, color);
                ptr = strtok(NULL, "|");
                idx++;
            }
            break;
        }
        currentLine++;
    }

    fclose(fq);
    fclose(fa);
    fclose(fb);
	 printf("Loaded question: %s\nLoaded answers: %s\nLoaded correct answer index: %d\n", question, reponse, e->correctAnswerIndices[questionIndex]);
}

    

void freeEnigme(Enigme *e) {
    if (e->background) {
        SDL_FreeSurface(e->background);
        e->background = NULL;
    }
    if (e->questionSurface) {
        SDL_FreeSurface(e->questionSurface);
        e->questionSurface = NULL;
    }
    for (int i = 0; i < 3; i++) {  
        if (e->answerSurfaces[i]) {
            SDL_FreeSurface(e->answerSurfaces[i]);
            e->answerSurfaces[i] = NULL;
        }
    }
    TTF_CloseFont(e->questionFont);
    TTF_CloseFont(e->answerFont);
    e->questionFont = NULL;
    e->answerFont = NULL;

}

void inithorloge(SDL_Surface *horloge[]) {
    
    for (int i = 0; i < 10; i++) {
        char path[100];
        sprintf(path, "horloge/%dhorloge.gif", i+1);
        horloge[i] = IMG_Load(path);
    }
}

void animateHorloge(SDL_Surface *horloge[], SDL_Surface *screen, int animationDuration) {
    static int lastImageIndex = 0; 
    static Uint32 lastUpdateTime = 0; 

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime > animationDuration) {
        lastUpdateTime = currentTime;
        lastImageIndex = (lastImageIndex + 1) % 10; 

        SDL_Rect pos = {930, 300, horloge[lastImageIndex]->w, horloge[lastImageIndex]->h};
        SDL_BlitSurface(horloge[lastImageIndex], NULL, screen, &pos);
        SDL_Flip(screen);
    }
}




void checkAnswer(Enigme *e, int rep, SDL_Surface *screen) {
    
    SDL_Surface *originalImage = (rep == e->correctAnswerIndices[e->questionIndex])
                                 ? IMG_Load("src_enigme/correct.png")
                                 : IMG_Load("src_enigme/wrong.png");

    if (!originalImage) {
        fprintf(stderr, "Erreur de chargement de l'image\n");
        return;
    }

    
    Mix_Chunk *soundEffect = Mix_LoadWAV(rep == e->correctAnswerIndices[e->questionIndex] ? "src_enigme/true.wav" : "src_enigme/false.wav");
    if (soundEffect) {
        Mix_PlayChannel(-1, soundEffect, 0);
    }

   
    SDL_Surface *zoomedImage;
    float zoomFactor = 1.0;
    int steps = 10;
    float stepSize = 0.1;

    for (int i = 0; i < steps; i++) {
        zoomedImage = rotozoomSurface(originalImage, 0, zoomFactor, 1);
        if (!zoomedImage) {
            fprintf(stderr, "Erreur de zoom de l'image\n");
            break;
        }

        
        SDL_Rect clearRect = {
            (screen->w - zoomedImage->w) / 2,
            (screen->h - zoomedImage->h) / 2,
            zoomedImage->w,
            zoomedImage->h
        };
        SDL_FillRect(screen, &clearRect, SDL_MapRGB(screen->format, 0, 0, 0));

       
        SDL_BlitSurface(e->background, NULL, screen, NULL); 
	 afficherEnigme(e, screen);  
     
        SDL_Rect pos = {
            (screen->w - zoomedImage->w) / 2,
            (screen->h - zoomedImage->h) / 2,
            0, 0
        };
        SDL_BlitSurface(zoomedImage, NULL, screen, &pos);
        SDL_Flip(screen);

        SDL_FreeSurface(zoomedImage);
        zoomFactor += stepSize;
        SDL_Delay(100);
    }

    SDL_FreeSurface(originalImage);
    if (soundEffect) {
        Mix_FreeChunk(soundEffect);
    }
 
}






