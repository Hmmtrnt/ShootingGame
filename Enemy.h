#pragma once

#include "Vec2.h"

class SceneMain;
class ShotBase;
class ShotNormal;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }
	// 敵の初期化
	void init();
	// SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// 敵の処理
	void update();
	// 描画
	void draw();
	// 敵の死亡
	void setDead(bool isDead) { m_isDead = isDead; }

	// 当たり判定
	bool isCol(ShotBase& shotBase);

	// 情報取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getColSize() const { return m_colSize; }


private:
	// 敵のスピード
	int m_speedY;
	// 敵のスピードの振れ幅
	int m_speedRand;
	// グラフィックハンドル
	int m_handle;
	// 敵の速さ
	int vecY;

	// 生死
	bool m_isDead;

	// SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;
};