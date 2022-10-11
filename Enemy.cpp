#include "DxLib.h"
#include "Enemy.h"
#include "game.h"

namespace
{
	// 敵のスピード
	constexpr float kSpeedY = 5.0f;
}

Enemy::Enemy()
{
	m_pMain = nullptr;
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
	DrawBox(m_pos.x, m_pos.y, m_pos.x + 30, m_pos.y + 30, GetColor(255, 255, 255), true);
	//DrawString(0, 16, "座標:%d", GetColor(255, 255, 255));
}