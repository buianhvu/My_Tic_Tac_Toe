#define SDL_MAIN_HANDLED
#include<stdio.h>
#include<SDL.h>


int main(int argc, char* argv[]){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}
	SDL_Window* window = NULL;
	window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s\n", SDL_GetError());
		return -1;
	}
	SDL_Delay(5000);
	//Destroy a window
	SDL_DestroyWindow(window);
	//This function cleans up all initialized subsystems
	SDL_Quit();

	return 0;


}