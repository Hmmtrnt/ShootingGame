#include "game.h"
#include "ShotNormal.h"
#include "SceneResult.h"

namespace
{
	// 弾のスピード
	constexpr float kShotSpeed = 25.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;
}

void ShotNormal::update()
{
	if (!m_isExist) return;
	m_pos += m_vec;
	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}

bool ShotNormal::isCol(Enemy& enemy)
{
	float shotLeft = getPos().x;
	float shotRight = getPos().x + getColSize().x / 2;
	float shotTop = getPos().y;
	float shotBottom = getPos().y + getColSize().y / 2;

	float enemyLeft = enemy.getPos().x;
	float enemyRight = enemy.getPos().x + enemy.getPos().x / 2;
	float enemyTop = enemy.getPos().y;
	float enemyBottom = enemy.getPos().y + enemy.getPos().y / 2;

	if (shotLeft > enemyRight)	return (new SceneResult);
	if (shotRight < enemyLeft)	return (new SceneResult);
	if (shotTop > enemyBottom)	return (new SceneResult);
	if (shotBottom < enemyTop)	return (new SceneResult);
}