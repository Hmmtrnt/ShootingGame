#include "game.h"
#include "ShotNormal.h"

namespace
{
	// 弾のスピード
	constexpr float kShotSpeedX = 25.0f;
	constexpr float kShotSpeedY = 0.0f;
}
// ショット開始
void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);
	// 弾の軌道
	m_vec.x = kShotSpeedX;
	m_vec.y = kShotSpeedY;
}
// 毎フレームの処理
void ShotNormal::update()
{
	if (!m_isExist) return;
	m_pos += m_vec;
	// 画面外に出たら消える
	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}