#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>
#include "GameScreenManager.h"
using namespace std;


//Globals
SDL_Window* g_window = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Renderer* g_renderer = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{

	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time
		g_old_time = SDL_GetTicks();


		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
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

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			//init PNG Loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
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

	//Release the renderer back into the wild
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get Current Events
	SDL_PollEvent(&e);

	//Handle Events
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		}
		break;
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}

void Render()
{
	//Clear the Screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//Update the screen
	SDL_RenderPresent(g_renderer);
}
