#ifndef WINDOW_INPUT
#define WINDOW_INPUT

#include <SDL2/SDL.h>
#include "SDL_events.h"

bool exitCondition(SDL_Event &e);
void resizeViewport(SDL_Event &e);

#endif