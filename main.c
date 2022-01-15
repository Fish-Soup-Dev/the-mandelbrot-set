#include <SDL2/SDL.h>
#include <stdio.h>
#undef main

float map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return ((float)x - (float)in_min) * ((float)out_max - (float)out_min) / ((float)in_max - (float)in_min) + (float)out_min;
}

int main(int argc, char *argv[])
{
    int width = 400;
    int height = 400;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("my nuts", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    int stop = 0;

    int ir = 0;
    int ig = 0;
    int ib = 0;

    for (int x = 0; x < height; x++)
    {
        if (stop != 0)
        {
            break;
        }

        for (int y = 0; y < width; y++)
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT)
            {
                stop = 1;
                break;
            }

            float a = map(y, 0, width, -1, 1) - 0.5;
            float b = map(x, 0, height, -1, 1);

            float ca = a;
            float cb = b;

            float n = 0;
            float z = 0;

            while(n < 100)
            {
                float aa = a * a - b * b;
                float bb = 2 * a * b;

                a = aa + ca;
                b = bb + cb;

                if(abs(a + b) > 16)
                {
                    break;
                }

                n ++;
            }
            
            float brightnessR = map(n, 0, 8, 0, 255);
            float brightnessG = map(b, 0, 100, 0, 255);
            float brightnessB = map(a, 0, 100, 0, 255);

            if(n == 100)
            {
                ir = 0;
                ig = 0;
                ib = 0;
            }
            else
            {
                ir = (int)brightnessR;
                ig = (int)brightnessG;
                ib = (int)brightnessB;
            }

            SDL_SetRenderDrawColor(renderer, ir, ig, ib, 255);
            SDL_RenderDrawPoint(renderer, y, x);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderPresent(renderer);
        }
    }

    while (1)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }
        if (stop != 0)
        {
            break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}