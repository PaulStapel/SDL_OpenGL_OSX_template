#include "SDL_events.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "SDL_video.h"

bool exitCondition(SDL_Event &e)
{
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            return true;
    }
    return false;
}

void resizeViewport(SDL_Event &e)
{
    while (SDL_PollEvent(&e)) {
        if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            int width = e.window.data1;
            int height = e.window.data2;
            glViewport(0,0,width,height);
        }
    }
}