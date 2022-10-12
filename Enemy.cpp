#include "DxLib.h"
#include "Enemy.h"
#include "game.h"
#include "SceneResult.h"

namespace
{
	// 敵のスピード
	constexpr float kSpeedY = 5.0f;
}

Enemy::Enemy()
{
	m_pMain = nullptr;
	m_isDead = false;
	vecY = 0;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	m_pos.x = 540.0f;
	m_pos.y = Game::kScreenWidth / 2;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_colSize.x = 30;
	m_colSize.y = 30;
	vecY = kSpeedY;
}

void Enemy::update()
{
	m_pos.y += vecY;
	if (m_pos.y < 0)
	{
		vecY = kSpeedY;
	}
	if (m_pos.y > Game::kScreenHeight - 30)
	{
		vecY = -kSpeedY;
	}
}

void Enemy::draw()
{
	if (m_isDead)	return;
	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
}