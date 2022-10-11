#pragma once

#include <vector>
#include "player.h"
#include "SceneBase.h"
#include "ShotBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	
	virtual ~SceneMain();

	// 初期化
	virtual void init();
	// 終了処理
	virtual void end();

	// 毎フレーム処理
	virtual SceneBase* update() override;

	// 毎フレーム描画
	virtual void draw() override;

	// 弾の生成
	bool createShotNormal(Vec2 pos);
private:
	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic;
	int m_hShotGraphic;
	// 敵のグラフィックハンドル
	int m_hEnemyGraphic;

	// プレイヤー
	Player m_player;
	// ショット
	std::vector<ShotBase*>m_pShotVt;
	// 表示位置
	Vec2 m_pos;
};