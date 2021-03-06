#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include <string>
#include "constants.h"
#include "Texture2D.h"
#include "LevelMap.h"
using namespace std;

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void AddGravity(float deltaTime);
	void SetPosition(Vector2D new_position);
	float GetCollisionRadius();
	Vector2D GetPosition();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive;  }

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	bool m_moving_left;
	bool m_moving_right;

	virtual void Jump();
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	float m_collision_radius;
	float m_movement_speed;
	FACING m_facing_direction;

	bool m_alive;

	int character_speed_mult;

private:
	LevelMap* m_current_level_map;
};

#endif //_CHARACTER_H



//TO DO ADD GRAVITY!!!!!