#pragma once

#include "Vec2.h"

class SceneMain;

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

	// 情報取得
	Vec2 getPos() const { return m_pos; }

private:
	// グラフィックハンドル
	int m_handle;
	//
	int vecY;
	// SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;
};