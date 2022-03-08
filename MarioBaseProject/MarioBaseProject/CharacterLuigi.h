#pragma once
#ifndef _LUIGI_H
#define _LUIGI_H
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);

};

#endif //_LUIGI_H