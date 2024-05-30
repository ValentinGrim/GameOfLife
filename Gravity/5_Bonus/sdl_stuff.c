#include "sdl_stuff.h"
#include "decl.h"
#include "sdl_win.h"
#include <unistd.h>
#include <SDL/SDL_mixer.h>

SDL_Surface *bmp;
SDL_Surface *bmp2;
SDL_Surface *screen;

typedef struct
{
        float x, y;
} vec2f;

vec2f positions[NB_BALLES];

extern void dragSouris(float x, float y);

int sdl_startup(config cfg)
{
    int i;
    // reset positions
    for (i = 0; i < NB_BALLES; i++) {
        positions[i].x = 0.0f;
        positions[i].y = 0.0f;
    }

    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 0;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(cfg.size_x, cfg.size_y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Unable to set  video: %s\n", SDL_GetError());
        return 0;
    }

    switch (cfg.ball_v) {

        case 1:
            bmp = SDL_LoadBMP("ball1.bmp");

            break;

        case 2:
            bmp = SDL_LoadBMP("ball2.bmp");
            break;
    }

    if (!bmp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetColorKey(bmp, SDL_SRCCOLORKEY, SDL_MapRGB(bmp->format, 0, 0, 0));

    return 1;
}

int sdl_loop(config cfg)
{

    // message processing loop
    SDL_Event event;
    static int leftButtonState = 0; // 0 = released , 1 = pressed
    while (SDL_PollEvent(&event)) {
        // check for messages
        switch (event.type) {
                // exit if the window is closed
            case SDL_QUIT:
                return 0;
                break;

                // check for keypresses
            case SDL_KEYDOWN: {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                // Si le bouton gauche de la souris est relache
                if (event.button.button & SDL_BUTTON_LEFT) {
                    leftButtonState = 0;
                }
                break;
            }

            case SDL_MOUSEBUTTONDOWN: {

                // Si le bouton gauche de la souris est presse
                if (event.button.button & SDL_BUTTON_LEFT) {
                    leftButtonState = 1;
                }
                break;
            }

        } // end switch
    } // end of message processing

    if (leftButtonState == 1) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        dragSouris((float)x / cfg.size_x, (float)(cfg.size_y - y) / cfg.size_y);
    }

    // DRAWING STARTS HERE

    // clear screen
    if (cfg.clear == 1) {

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    }

    // dessine les  balles

    int i;

    for (i = 0; i < cfg.nbballs; i++) {
        // position de la balle en pixels
        SDL_Rect dstrect;
        dstrect.x = cfg.size_x * positions[i].x - bmp->w / 2;
        dstrect.y = cfg.size_y - cfg.size_y * positions[i].y - bmp->h / 2;

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);
    }

    // DRAWING ENDS HERE

    // finally, update the screen :)
    SDL_Flip(screen);

    usleep(1000);

    return 1;
}

void sdl_setBallPosition(int balleIndex, float x, float y)
{

    positions[balleIndex].x = x;
    positions[balleIndex].y = y;
}

void sdl_clean()
{
    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
}
