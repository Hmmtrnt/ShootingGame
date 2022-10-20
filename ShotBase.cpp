#include "DxLib.h"
#include "ShotBase.h"

namespace
{
	// 表示位置
	constexpr float kPosX = 0.0f;
	constexpr float kPosY = 0.0f;
	// 弾のサイズ
	constexpr float kSizeX = 10.0f;
	constexpr float kSizeY = 5.0f;
	// 弾の移動
	constexpr float kVecX = 0.0f;
	constexpr float kVecY = 0.0f;
	// 弾が出る位置
	constexpr float kPosShotX = 35.0f;
	constexpr float kPosShotY = 25.0f;
}

ShotBase::ShotBase()
{
	m_pos.x = kPosX;		// 表示位置
	m_pos.y = kPosY;
	m_size.x = kSizeX;	// 弾のサイズ
	m_size.y = kSizeY;
	m_vec.x = kVecX;		// 弾の移動
	m_vec.y = kVecX;

	m_isExist = false;	// 弾の有無
}
// ショット開始
void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	// 自機から弾が出る位置
	pos.x += kPosShotX;		// X軸
	pos.y += kPosShotY;		// Y軸

	m_pos = pos;
}
// 毎フレームの処理
void ShotBase::update()
{
	if (!m_isExist) return;
}
// 描画
void ShotBase::draw()
{
	if (!m_isExist) return;
	
	DrawOval((int)m_pos.x, (int)m_pos.y, (int)m_size.x, (int)m_size.y, GetColor(0, 0, 0), true);
}