#include <iostream>
#include <SDL3/SDL.h>

int main(){

  SDL_Window *window;

  if(!SDL_Init(SDL_INIT_VIDEO)){
    std::cerr << "SDL init failed with error " << SDL_GetError() << std::endl;
    return 1;
  }

  window = SDL_CreateWindow("Fraycast", 800, 600, 0);

  if(window == NULL){
    std::cerr << "SDL window init failed with error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Delay(5000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;

}