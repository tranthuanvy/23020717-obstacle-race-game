#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP =32;
const int FRAME_PER_SECOND =35;

static SDL_Window * gWindow =nullptr;
static SDL_Renderer* gRenderer = nullptr;
static SDL_Event e;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define COIN_TILE 5
#define OSTACLE1 4
#define OSTACLE2 3


typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;

};

typedef struct map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
} ;


#endif // COMMON_FUNC_H_
