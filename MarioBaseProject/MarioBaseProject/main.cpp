#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>
using namespace std;


//Globals
SDL_Window* g_window = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();

int main(int argc, char* args[])
{

	if (InitSDL())
	{
		SDL_Delay(5000);
	}

	CloseSDL();
	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Setup passed to create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//Did it work?
		if (g_window == nullptr)
		{
			cout << "Window coult not be created. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}

void CloseSDL()
{
	//Release the window back into the wild
	SDL_DestroyWindow(g_window);
	//Oh No
	g_window = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
