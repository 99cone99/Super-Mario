#pragma once
#ifndef _MARIO_H
#define _MARIO_H
#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);

};

#endif //_MARIO_H