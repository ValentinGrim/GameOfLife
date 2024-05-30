#ifndef SDL_STUFF_INCLUDED
#define SDL_STUFF_INCLUDED

#ifndef NO_STDIO_REDIRECT
    #define NO_STDIO_REDIRECT
#endif

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

#include "sdl_win.h"

#define BALL_RADIUS (16.0f / (float)512)

int sdl_loop(config cfg);
int sdl_startup(config cfg);
void sdl_clean();

// la fenettre s'etend de [-1,-1] � [+1,+1]
void sdl_setBallPosition(int balleIndex, float x, float y);

#endif
