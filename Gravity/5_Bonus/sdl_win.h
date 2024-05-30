#ifndef SDL_WIN_H
#define SDL_WIN_H


#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL/SDL.h>
#endif

typedef struct configuration_decl
{

  int size_x;
  int size_y;
  int music_state;
  int ball_v;
  int nbballs;
  int clear;

}config;

int sdlMenu(config cfg);

int sdlSettings(config * cfg);

int sdlPlay(config cfg);

#endif
