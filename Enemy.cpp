#include "DxLib.h"
#include "Enemy.h"
#include "game.h"
#include "SceneResult.h"
//#include "ShotBase.h"
#include "ShotNormal.h"

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
	m_speedY = 25;
	m_pos.x = 540.0f;
	m_pos.y = Game::kScreenHeight / 2;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_colSize.x = 30;
	m_colSize.y = 30;
	vecY = m_speedY;
}

void Enemy::update()
{
	m_speedRand = GetRand(25) + 1;

	if (m_isDead)	return;
	m_pos.y += vecY;
	if (m_pos.y < 0)
	{
		m_speedY = m_speedRand;
		vecY = m_speedY;
	}
	if (m_pos.y > Game::kScreenHeight - 30)
	{
		m_speedY = m_speedRand;
		vecY = -m_speedY;
	}
}

void Enemy::draw()
{
	if (m_isDead)	return;
	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_colSize.x, m_pos.y + m_colSize.y, GetColor(255, 255, 255), true);
}

bool Enemy::isCol(ShotBase& shotBase)
{
	float shotLeft = shotBase.getPos().x;
	float shotRight = shotBase.getPos().x + shotBase.getSize().x;
	float shotTop = shotBase.getPos().y;
	float shotBottom = shotBase.getPos().y + shotBase.getSize().y;

	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + getColSize().x;
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + getColSize().y;

	//return true;

	if (shotLeft > enemyRight)	return false;
	if (shotRight < enemyLeft)	return false;
	if (shotTop > enemyBottom)	return false;
	if (shotBottom < enemyTop)	return false;

	return true;

	/*if (shotLeft < enemyRight)	return false;
	if (shotRight > enemyLeft)	return false;
	if (shotTop < enemyBottom)	return false;
	if (shotBottom > enemyTop)	return false;

	return true;*/
}