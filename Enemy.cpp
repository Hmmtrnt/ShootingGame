#include "DxLib.h"
#include "Enemy.h"
#include "game.h"

namespace
{
	// 敵のスピード
	constexpr float kSpeedY = 15.0f;
	// 敵の右下の頂点座標
	constexpr int kBottomRightX = 50;
	constexpr int kBottomRightY = 50;
}

Enemy::Enemy()
{
	m_pMain = nullptr;
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
}

void Enemy::update()
{
	m_pos.y -= kSpeedY;
	if (m_pos.y < 0)
	{
		m_pos.y += kSpeedY;
	}
	else if (m_pos.y > Game::kScreenWidth)
	{
		m_pos.y -= kSpeedY;
	}
}

void Enemy::draw()
{
	DrawBox(m_pos.x, m_pos.y, kBottomRightX, kBottomRightY, GetColor(255, 255, 255), true);
}