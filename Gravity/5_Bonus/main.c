#include "balle.h"
#include "vecteur.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "sdl_stuff.h"
#include "sdl_win.h"
#include "fpstimer.h"
#include <stdio.h>
#include <SDL/SDL.h>

int main()
{

  config cfg;

  cfg.size_x = 512;
  cfg.size_y = 512;
  cfg.music_state = 1;
  cfg.ball_v = 1;
  cfg.nbballs = 5;
  cfg.clear = 1;

  int continuer = 1;

  while(continuer == 1)
  {

    if(continuer == 1)
    {

      continuer = sdlMenu(cfg);

    }

    if(continuer == 2)
    {

      continuer = sdlPlay(cfg);

    }

    if(continuer == 3)
    {

       continuer = sdlSettings(&cfg);

    }

  }

  return 0;

}
