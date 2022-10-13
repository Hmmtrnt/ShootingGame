#include "DxLib.h"
#include "ShotBase.h"

ShotBase::ShotBase()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_size.x = 10.0f;
	m_size.y = 10.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}

ShotBase::~ShotBase()
{

}

void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	m_pos = pos;
}

void ShotBase::update()
{
	if (!m_isExist) return;
}

void ShotBase::draw()
{
	if (!m_isExist) return;
	DrawBox(m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GetColor(255, 255, 255), true);
}

//bool ShotBase::isCol(Enemy& enemy)
//{
//	float shotLeft = getPos().x;
//	float shotRight = getPos().x + getSize().x;
//	float shotTop = getPos().y;
//	float shotBottom = getPos().y + getSize().y;
//
//	float enemyLeft = enemy.getPos().x;
//	float enemyRight = enemy.getPos().x + enemy.getColSize().x;
//	float enemyTop = enemy.getPos().y;
//	float enemyBottom = enemy.getPos().y + enemy.getColSize().y;
//
//	if (shotLeft < enemyRight)	return false;
//	if (shotRight > enemyLeft)	return false;
//	if (shotTop < enemyBottom)	return false;
//	if (shotBottom > enemyTop)	return false;
//	return true;
//}