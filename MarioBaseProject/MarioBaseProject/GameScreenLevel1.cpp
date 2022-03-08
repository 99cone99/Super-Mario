#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();

}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_mario;
	m_mario = nullptr;
	delete m_luigi;
	m_luigi = nullptr;

}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	
	//draw mario
	m_mario->Render();

	//draw luigi
	m_luigi->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (Collisions::Instance()->Circle(m_mario, m_luigi))
	{
		cout << "Cirlce Hit!" << endl;
	}

	if (Collisions::Instance()->Box(m_mario->GetCollisionBox(), m_luigi->GetCollisionBox()))
	{
		cout << "Box Hit!" << endl;
	}

	//update character
	m_mario->Update(deltaTime, e);
	m_luigi->Update(deltaTime, e);

}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//Set up player characer
	m_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	m_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(100, 330), m_level_map);

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}