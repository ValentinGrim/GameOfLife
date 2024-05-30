#include "sdl_stuff.h"
#include "sdl_win.h"
#include "decl.h"
#include "fpstimer.h"
#include "balle.h"
#include "vecteur.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL_mixer.h>
#include <time.h>

Balle gBalleTab[NB_BALLES];

void dragSouris(float x, float y)
{
    gBalleTab[0].position.x=x; 		//Récupération de la position x de la souris pour la position de la première balle
    gBalleTab[0].position.y=y; 		//Récupération de la position y de la souris pour la position de la première balle
}

int sdlMenu(config cfg)
{

  SDL_Rect position;

  SDL_Surface * bPlayImg;
  SDL_Surface * bSetImg;
  SDL_Surface * bExitImg;
  SDL_Surface * background;
  Mix_Music * musique;

  SDL_Surface *window = NULL;

  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

  window = SDL_SetVideoMode(256, 512, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

  if (window == NULL)
  {

      printf("Unable to open menu : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);

  }

  SDL_WM_SetCaption("Meme Bonus", NULL);
  SDL_FillRect(window, NULL, SDL_MapRGB(window->format,0,0,0));

  bPlayImg = SDL_LoadBMP("Button_Play.bmp");
  bSetImg = SDL_LoadBMP("Button_Settings.bmp");
  bExitImg = SDL_LoadBMP("Button_Exit.bmp");
  background = SDL_LoadBMP("menu.bmp");

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer

  {

    printf("%s", Mix_GetError());

  }

  if(cfg.music_state == 1)
  {

    musique = Mix_LoadMUS("menu.mp3");
    Mix_PlayMusic(musique, -1);

  }

  int continuer = 1;
  while(continuer == 1)
  {

    SDL_WaitEvent(&event);
    switch(event.type)
    {

      case SDL_QUIT:
          continuer = 0;
          break;

      case SDL_MOUSEBUTTONUP:
          if((event.button.y > 422 && event.button.y < 474 && event.button.x > 27 && event.button.x < 229) &SDL_BUTTON_LEFT)
          {

              continuer = 0;

          }

          if((event.button.y > 38 && event.button.y < 89 && event.button.x > 27 && event.button.x < 229) &SDL_BUTTON_LEFT)
          {

              continuer = 2;

          }

          if((event.button.y > 166 && event.button.y < 218 && event.button.x > 27 && event.button.x < 229) &SDL_BUTTON_LEFT)
          {

              continuer = 3;

          }
      break;

    }

    SDL_Flip(window);

    position.x = 0;
    position.y =0;
    SDL_BlitSurface(background, NULL, window, &position);

    position.x = 28;
    position.y = 39;
    SDL_BlitSurface(bPlayImg, NULL, window, &position);

    position.x = 28;
    position.y = 167;
    SDL_BlitSurface(bSetImg, NULL, window, &position);

    position.x = 28;
    position.y = 423;
    SDL_BlitSurface(bExitImg, NULL, window, &position);


  }

  if(cfg.music_state == 1)
  {

    Mix_FreeMusic(musique);
    Mix_CloseAudio();

  }

  sdl_clean();

  return continuer;

}

int sdlSettings(config * cfg)
{

  SDL_Rect position;

  srand(time(NULL));

  SDL_Surface * b431Img, * b432Img, * b1691Img, * b1692Img, * bMusicY, * bMusicN, * bBack, * bBall1, * bBall2,/* * bBall3, * bBall4, */* bClearY, * bClearN;
  SDL_Surface * b2B, * b5B, * b25B, * bRandB;
  SDL_Surface * window = NULL;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

  window = SDL_SetVideoMode(925, 512, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

  if (window == NULL)
  {

      printf("Unable to open settings : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);

  }

  SDL_WM_SetCaption("Settings", NULL);
  SDL_FillRect(window, NULL, SDL_MapRGB(window->format,245,80,0));

  b431Img = SDL_LoadBMP("4tiers1.bmp");
  b432Img = SDL_LoadBMP("4tiers2.bmp");
  b1691Img = SDL_LoadBMP("16neuvieme1.bmp");
  b1692Img = SDL_LoadBMP("16neuvieme2.bmp");
  bMusicY = SDL_LoadBMP("music_on.bmp");
  bMusicN = SDL_LoadBMP ("music_off.bmp");
  bBack = SDL_LoadBMP ("back.bmp");
  bBall1 = SDL_LoadBMP("bTenis.bmp");
  bBall2 = SDL_LoadBMP("bDennis.bmp");
  //bBall3 = SDL_LoadBMP("bBodin.bmp");
  //bBall4 = SDL_LoadBMP("bBannier.bmp");
  bClearY = SDL_LoadBMP("clear_on.bmp");
  bClearN = SDL_LoadBMP("clear_off.bmp");
  b2B = SDL_LoadBMP("2balls.bmp");
  b5B = SDL_LoadBMP("5balls.bmp");
  b25B = SDL_LoadBMP("25balls.bmp");
  bRandB = SDL_LoadBMP("Random_Balls.bmp");

  int continuer = 1;

  while(continuer == 1)
  {

    SDL_WaitEvent(&event);

    switch(event.type)
    {

      case SDL_QUIT:
          continuer = 0;
          break;

      case SDL_MOUSEBUTTONUP:
          if((event.button.y > 38 && event.button.y < 89 && event.button.x > 24 && event.button.x < 226) &SDL_BUTTON_LEFT)
          {

            cfg->size_x = 512;
            cfg->size_y = 512;

          }

          if((event.button.y > 38 && event.button.y < 89 && event.button.x > 249 && event.button.x < 451) &SDL_BUTTON_LEFT)
          {

            cfg->size_x = 1024;
            cfg->size_y = 1024;

          }

          if((event.button.y > 38 && event.button.y < 89 && event.button.x > 474 && event.button.x < 676) &SDL_BUTTON_LEFT)
          {

            cfg->size_x = 1366;
            cfg->size_y = 768;

          }

          if((event.button.y > 38 && event.button.y < 89 && event.button.x > 699 && event.button.x < 901) &SDL_BUTTON_LEFT)
          {

            cfg->size_x = 1920;
            cfg->size_y = 1080;

          }

          if((event.button.y > 422 && event.button.y < 474 && event.button.x > 24 && event.button.x < 226) &SDL_BUTTON_LEFT)
          {

              if(cfg->music_state == 1)
              {

                cfg->music_state = 0;

              }

              else
              {

                cfg->music_state = 1;

              }

          }

          if((event.button.y > 422 && event.button.y < 474 && event.button.x > 249 && event.button.x < 451) &SDL_BUTTON_LEFT)
          {

              if(cfg->clear == 1)
              {

                cfg->clear = 0;

              }

              else
              {

                cfg->clear = 1;

              }

          }

          if((event.button.y > 422 && event.button.y < 474 && event.button.x > 699 && event.button.x < 901) &SDL_BUTTON_LEFT)
          {

            continuer = 0;

          }

          if((event.button.y > 294 && event.button.y < 345 && event.button.x > 24 && event.button.x < 226) &SDL_BUTTON_LEFT)
          {

            cfg->ball_v = 1;

          }

          if((event.button.y > 294 && event.button.y < 345 && event.button.x > 249 && event.button.x < 451) &SDL_BUTTON_LEFT)
          {

            cfg->ball_v = 2;

          }

          if((event.button.y > 166 && event.button.y < 217 && event.button.x > 24 && event.button.x < 226) &SDL_BUTTON_LEFT)
          {

            cfg->nbballs = 2;

          }

          if((event.button.y > 166 && event.button.y < 217 && event.button.x > 249 && event.button.x < 451) &SDL_BUTTON_LEFT)
          {

            cfg->nbballs = 5;

          }

          if((event.button.y > 166 && event.button.y < 217 && event.button.x > 474 && event.button.x < 676) &SDL_BUTTON_LEFT)
          {

            cfg->nbballs = 25;

          }

          if((event.button.y > 166 && event.button.y < 217 && event.button.x > 699 && event.button.x < 901) &SDL_BUTTON_LEFT)
          {

            cfg->nbballs = rand()%25+1;

          }

          /*if((event.button.y > 294 && event.button.y < 345 && event.button.x > 474 && event.button.x < 676) &SDL_BUTTON_LEFT)
          {

            cfg->ball_v = 3;

          }

          if((event.button.y > 294 && event.button.y < 345 && event.button.x > 699 && event.button.x < 901) &SDL_BUTTON_LEFT)
          {

            cfg->ball_v = 4;

          }*/

      break;

    }

    if(cfg->music_state == 1)
    {

      position.x = 25;
      position.y = 423;
      SDL_BlitSurface(bMusicY, NULL, window, &position);

    }

    else
    {

      position.x = 25;
      position.y = 423;
      SDL_BlitSurface(bMusicN, NULL, window, &position);

    }

    if(cfg->clear == 1)
    {

      position.x = 250;
      position.y = 423;
      SDL_BlitSurface(bClearY, NULL, window, &position);

    }

    else
    {

      position.x = 250;
      position.y = 423;
      SDL_BlitSurface(bClearN, NULL, window, &position);

    }

    position.x = 25;
    position.y = 39;
    SDL_BlitSurface(b431Img, NULL, window, &position);

    position.x = 250;
    position.y = 39;
    SDL_BlitSurface(b432Img, NULL, window, &position);

    position.x = 475;
    position.y = 39;
    SDL_BlitSurface(b1691Img, NULL, window, &position);

    position.x = 700;
    position.y = 39;
    SDL_BlitSurface(b1692Img, NULL, window, &position);

    position.x = 700;
    position.y = 423;
    SDL_BlitSurface(bBack, NULL, window, &position);

    position.x = 25;
    position.y = 295;
    SDL_BlitSurface(bBall1, NULL, window, &position);

    position.x = 250;
    position.y = 295;
    SDL_BlitSurface(bBall2, NULL, window, &position);

    position.x = 25;
    position.y = 167;
    SDL_BlitSurface(b2B, NULL, window, &position);

    position.x = 250;
    position.y = 167;
    SDL_BlitSurface(b5B, NULL, window, &position);

    position.x = 475;
    position.y = 167;
    SDL_BlitSurface(b25B, NULL, window, &position);

    position.x = 700;
    position.y = 167;
    SDL_BlitSurface(bRandB, NULL, window, &position);

    /*position.x = 475;
    position.y = 295;
    SDL_BlitSurface(bBall3, NULL, window, &position);

    position.x = 700;
    position.y = 295;
    SDL_BlitSurface(bBall4, NULL, window, &position);*/

    SDL_Flip(window);

  }

    sdl_clean();

    return 1;

}

int sdlPlay(config cfg)
{

      Mix_Music * music;

      srand(time(NULL));

      if(!sdl_startup(cfg))
          return -1;

      fpsInit();

      float dt; 			// Déclaration de la variable delta
      int i;

            int a;
            for(a = 0; a < cfg.nbballs; a++)
            {

              gBalleTab[a] = chargerBalle("balle.txt");
              gBalleTab[a].vitesse.x = rand()%5+1;
              gBalleTab[a].vitesse.y = rand()%5+1;

            }

          if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer

          {

            printf("%s", Mix_GetError());

          }

      if(cfg.music_state == 1)
      {

        if(cfg.ball_v == 2)
        {

            music = Mix_LoadMUS("dennis.mp3");
            Mix_PlayMusic(music, -1);

        }

      }


       //program main loop
      do
      {

          fpsStep();

          dt=fpsGetDeltaTime();  		// Assigne le temps entre deux frames à la variable dt
      for(i=0; i<NB_BALLES; i++) 		// Boucle qui met à jour la position de chaque balle, qui limite ses déplacement à la fenêtre et affiche la balle
      {

          majPosition(&gBalleTab[i], dt); 	// Mise à jour de la position de chaque balle en fonction de dt

          if(gBalleTab[i].position.x < BALL_RADIUS) 	// Condition si la balle touche le bord gauche
          {

              gBalleTab[i].vitesse.x = (-gBalleTab[i].vitesse.x) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
              gBalleTab[i].position.x = BALL_RADIUS; 		      // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran

          }

          if(gBalleTab[i].position.x > 1 - BALL_RADIUS) 	// Condition si la balle touche le bord droit
          {

              gBalleTab[i].vitesse.x = (-gBalleTab[i].vitesse.x) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
              gBalleTab[i].position.x = 1 - BALL_RADIUS; 		      // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran


          }

          if(gBalleTab[i].position.y < BALL_RADIUS) // Condition si la balle touche le bord du haut
          {

             gBalleTab[i].vitesse.y = (-gBalleTab[i].vitesse.y) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
             gBalleTab[i].position.y = BALL_RADIUS; 		     // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran

          }

          if(gBalleTab[i].position.y > 1 - BALL_RADIUS) // Condition si la balle touche le bord du bas
          {

              gBalleTab[i].vitesse.y = (-gBalleTab[i].vitesse.y) * 1; // Inversement de la vitesse pour faire partir la balle dans l'autre sens et reduction de la vitesse (perte d'energie)
              gBalleTab[i].position.y = 1 - BALL_RADIUS; 		      // Mise à jour de la position de la balle pour qu'elle ne sorte pas de l'écran

          }


          sdl_setBallPosition(i,gBalleTab[i].position.x,gBalleTab[i].position.y); // Affichage de la balle

      }

      }
      while(sdl_loop(cfg));
      // end main loop

      if(cfg.music_state == 1)
      {

        Mix_FreeMusic(music);
        Mix_CloseAudio();

      }

      sdl_clean();
  return 0;

}
