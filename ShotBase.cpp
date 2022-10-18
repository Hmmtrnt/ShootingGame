#include "DxLib.h"
#include "ShotBase.h"

ShotBase::ShotBase()
{
	m_pos.x = 0.0f;		// 表示位置
	m_pos.y = 0.0f;
	m_size.x = 10.0f;	// 弾のサイズ
	m_size.y = 5.0f;
	m_vec.x = 0.0f;		// 弾の移動
	m_vec.y = 0.0f;

	m_isExist = false;	// 弾の有無
}
// ショット開始
void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	// 自機から弾が出る位置
	pos.x += 35.0f;		// X軸
	pos.y += 25.0f;		// Y軸

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
	
	DrawOval(m_pos.x, m_pos.y, m_size.x, m_size.y, GetColor(0, 0, 0), true);
}