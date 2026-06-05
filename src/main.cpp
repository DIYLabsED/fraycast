#include <iostream>
#include <SDL3/SDL.h>


const int lodevMapWidth = 24, lodevMapHeight = 24;
int lodevMap[lodevMapWidth][lodevMapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define COLOR_RED 255, 0, 0, 255
#define COLOR_GREEN 0, 255, 0, 255
#define COLOR_BLUE 0, 0, 255, 255
#define COLOR_YELLOW 255, 255, 0, 255

#define COLOR_DIM_RED 128, 0, 0, 255
#define COLOR_DIM_GREEN 0, 128, 0, 255
#define COLOR_DIM_BLUE 0, 0, 128, 255
#define COLOR_DIM_YELLOW 128, 128, 0, 255


void raycast(SDL_Renderer* renderer);


int main(){

  SDL_Window *window;
  SDL_Renderer *renderer;

  if(!SDL_Init(SDL_INIT_VIDEO)){
    std::cerr << "SDL init failed with error " << SDL_GetError() << std::endl;
    return 1;
  }

  if(!SDL_CreateWindowAndRenderer("Fraycast", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)){
    std::cerr << "SDL window and render init failed with error " << SDL_GetError() << std::endl;
    return 1;
  }

  bool run = true;
  while(run){

    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_EVENT_QUIT){
        run = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    raycast(renderer);

    SDL_RenderPresent(renderer);

  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;

}

void raycast(SDL_Renderer* renderer){

  // Player and camera variables
  double playerPosX = 12, playerPosY = 20;
  double lookDirX = -1, lookDirY = 0;
  double cameraPlaneX = 0, cameraPlaneY = 0.66;

  // Loop over each x coordinate on screen
  for(int screenX = 0; screenX < SCREEN_WIDTH; screenX++){

    // Calculate ray direction
    double lineCameraX = 2.0 * screenX / SCREEN_WIDTH - 1.0;                  // x coordinate of current line in camera's plane, normalized so left is -1, right is 1
    double rayDirX = lookDirX + cameraPlaneX * lineCameraX;                   // calculate direction of ray based on player look angle, and camera pos
    double rayDirY = lookDirY + cameraPlaneY * lineCameraX;

    // Calculate vars needed for DDA
    int mapCellX = int(playerPosX);                                           // which cell of the map we are in, since the player pos is a float, convert it to an int
    int mapCellY = int(playerPosY);

    double raySideDistX, raySideDistY;                                        // distance from current position of ray to the next nearest x or y wall

    double rayDeltaDistX = std::abs(1 / rayDirX);                             // the paper mentions using 1e30 as a fallback here if rayDirX/Y is 0, but thanks to IEEE 754
    double rayDeltaDistY = std::abs(1 / rayDirY);                          // we can ignore that part

    double distanceToWall;                                                    // distance to the wall the ray hits, if it does

    int stepX, stepY;                                                         // either -1 or 1, representing which direction to step during ray collision check

    bool hit = 0;                                                             // did the ray hit a wall?
    int side;                                                                 // 0 if the side of the wall that was hit faces the x axis, 1 if y axis

    // Calculate distances for X axis
    if(rayDirX < 0){
      stepX = -1;
      raySideDistX = (playerPosX - mapCellX) * rayDeltaDistX;
    }
    else{
      stepX = 1;
      raySideDistX = (mapCellX + 1 - playerPosX) * rayDeltaDistX;
    }

    // Calculate distances for Y axis
    if(rayDirY < 0){
      stepY = -1;
      raySideDistY = (playerPosY - mapCellY) * rayDeltaDistY;
    }
    else{
      stepY = 1;
      raySideDistY = (mapCellY + 1 - playerPosY) * rayDeltaDistY;
    }

    // Run DDA algorithm
    while(!hit){

      // Move to next cell in map along the ray
      if(raySideDistX < raySideDistY) {
        raySideDistX += rayDeltaDistX;
        mapCellX += stepX;
        side = 0;
      }
      else{
        raySideDistY += rayDeltaDistY;
        mapCellY += stepY;
        side = 1;
      }

      // Check if ray has hit a wall
      if(lodevMap[mapCellX][mapCellY] > 0) hit = 1;

      // Calculate length of ray
      if(side == 0) distanceToWall = (raySideDistX - rayDeltaDistX);
      else distanceToWall = (raySideDistY - rayDeltaDistY);

    }

    // Draw line on screen
    int lineHeight = (int)(SCREEN_HEIGHT / distanceToWall);
    int lineOffset = (int)(SCREEN_HEIGHT - lineHeight) / 2;
    int lineDrawStart = lineOffset;
    int lineDrawEnd = lineOffset + lineHeight;

    switch(lodevMap[mapCellX][mapCellY]){

      case 1:
        if(side == 1) SDL_SetRenderDrawColor(renderer, COLOR_DIM_RED);
        else SDL_SetRenderDrawColor(renderer, COLOR_RED);
        break;

      case 2:
        if(side == 1) SDL_SetRenderDrawColor(renderer, COLOR_DIM_GREEN);
        else SDL_SetRenderDrawColor(renderer, COLOR_GREEN);
        break;

      case 3:
        if(side == 1) SDL_SetRenderDrawColor(renderer, COLOR_DIM_BLUE);
        else SDL_SetRenderDrawColor(renderer, COLOR_BLUE);
        break;

      case 4:
        if(side == 1) SDL_SetRenderDrawColor(renderer, COLOR_DIM_YELLOW);
        else SDL_SetRenderDrawColor(renderer, COLOR_YELLOW);
        break;

    }

    SDL_RenderLine(renderer, screenX, lineDrawStart, screenX, lineDrawEnd);

  }

}