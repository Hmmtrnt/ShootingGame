#pragma once
#include "SceneBase.h"

class SceneFail : public SceneBase
{
public:
	SceneFail();
	
	virtual ~SceneFail() {}

	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;

	// 背景
	int m_fieldHandle;
	// 敵のグラフィックハンドル
	int m_enemyHandle;

	// 地面の高さ
	float m_fieldY;

	// 敵の表示位置
	Vec2 m_pos;
	// 敵のサイズ
	Vec2 m_size;
	// 敵の移動
	Vec2 m_vec;
};