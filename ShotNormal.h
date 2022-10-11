#pragma once

#include "Enemy.h"
#include "ShotBase.h"

class ShotNormal : public ShotBase
{
public:
	ShotNormal() {}
	virtual ~ShotNormal() {}

	// ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

	// エネミーとの衝突判定
	bool isCol(Enemy& enemy);

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getGraphSize() const { return m_graphSize; }
	Vec2 getColSize() const { return m_colSize; }

private:
	// グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;
};