#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player() {}

	// グラフィックデータ設定
	void setHandle(int handle);

	// プレイヤーの初期化
	void init();

	// SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 処理
	void update();

	// 描画
	void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

private:
	//グラフィックハンドル
	int m_Playerhandle;
	// 弾の発射間隔
	int m_shotInterval;

	// SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;
	// プレイヤーグラフィックの幅
	Vec2 m_size;
};