#include "GameScreenLevel1.h"
#include <iostream>


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
	//delete m_luigi;
	//m_luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_enemies.clear();
	m_coins.clear();

	m_enemy_respawn_time = 10.0f;
}

void GameScreenLevel1::Render()
{
	//draw koopas
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	for (size_t i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}
	
	//draw mario
	m_mario->Render();

	//draw luigi
	//m_luigi->Render();

	//Draw Pow block
	m_pow_block->Render();

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 8.0f;

		//end shake after durian
		if (m_shake_time <= 0.0f)
		{
			m_screenshake = false;
			m_background_yPos = 0.0f;
		}
	}

	//for (size_t i = 0; i < m_coins.size(); i++)
//	{
//
	//}

	//if (Collisions::Instance()->Circle(m_mario, m_luigi))
	//{
	//	//cout << "Circle Hit!" << endl;
	//}

	//if (Collisions::Instance()->Box(m_mario->GetCollisionBox(), m_luigi->GetCollisionBox()))
	//{
	//	//cout << "Box Hit!" << endl;
	//}

	//update character
	m_mario->Update(deltaTime, e);
	//m_luigi->Update(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock();

	for (size_t i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Update(deltaTime, e);
	}

	m_enemy_respawn_time -= deltaTime;


	if (m_enemy_respawn_time <= 0)
	{
		CreateKoopa(Vector2D(0, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(480, 32), FACING_LEFT, KOOPA_SPEED);
		m_enemy_respawn_time = 10.0f;
	}


}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/background.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	//Sets up the map
	SetLevelMap();

	//Set up player characer
	m_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	//m_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);

	CreateKoopa(Vector2D(0, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(480, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoin(Vector2D(235, 105));
	CreateCoin(Vector2D(265, 105));
	CreateCoin(Vector2D(105, 235));
	CreateCoin(Vector2D(395, 235));
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

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	
	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(m_mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (m_mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				m_mario->CancelJump();
			}
		}
	}
	/*if (Collisions::Instance()->Box(m_luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (m_luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				m_luigi->CancelJump();
			}
		}
	}*/
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}

			//now do the update
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], m_mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						m_mario->SetAlive(false);
					}
				}
				/*if (Collisions::Instance()->Circle(m_enemies[i], m_luigi))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						m_luigi->SetAlive(false);
					}
				}*/
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(m_koopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	m_coin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);
	m_coins.push_back(m_coin);
}