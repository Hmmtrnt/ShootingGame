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

	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
}

bool Enemy::isCol(ShotBase& shot)
{
	float shotLeft = shot.getPos().x;
	float shotRight = /*shot.getPos().x + */shot.getSize().x * 2;
	float shotTop = shot.getPos().y;
	float shotBottom = /*shot.getPos().y + */shot.getSize().y * 2;

	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + getColSize().x;
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + getColSize().y;

	if (shotLeft > enemyRight)	return (new SceneResult);
	if (shotRight < enemyLeft)	return (new SceneResult);
	if (shotTop > enemyBottom)	return (new SceneResult);
	if (shotBottom < enemyTop)	return (new SceneResult);
	/*if (shotLeft > enemyRight)
	{
		DrawString(16, 16, "当たりました", GetColor(255, 255, 255));
		return 0;
	}
	if (shotRight < enemyLeft)
	{
		DrawString(16, 16, "当たりました", GetColor(255, 255, 255));
		return 0;
	}
	if (shotTop > enemyBottom)
	{
		DrawString(16, 16, "当たりました", GetColor(255, 255, 255));
		return 0;
	}
	if (shotBottom < enemyTop)
	{
		DrawString(16, 16, "当たりました", GetColor(255, 255, 255));
		return 0;
	}*/
}