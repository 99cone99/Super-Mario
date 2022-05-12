#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Texture2D.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include <vector>

class Texture2D;

class Character;

class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	void DoScreenShake();

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();

	CharacterMario* m_mario;
	CharacterLuigi* m_luigi;
	CharacterKoopa* m_koopa;
	CharacterCoin* m_coin;

	void SetLevelMap();

	LevelMap* m_level_map;

	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	int score;

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);

	vector<CharacterKoopa*> m_enemies;
	vector<CharacterCoin*> m_coins;

	float m_enemy_respawn_time;
};


#endif //_GAMESCREENLEVEL1_H
