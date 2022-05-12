#pragma once
#ifndef _CHARACTERCOIN_H
#define CHARACTERCOIN
#include "Character.h"


class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterCoin();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	void CoinCollected();
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay = 0;
	float m_current_frame = 0;
	int m_sprite_state = 0;

	bool m_collected;
};

#endif //_CHARACTERCOIN_H