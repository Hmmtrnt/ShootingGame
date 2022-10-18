#pragma once
#include "SceneBase.h"

class SceneFail : public SceneBase
{
public:
	SceneFail();
	virtual ~SceneFail() {}
	// 初期化
	virtual void init() override;
	// 終了
	virtual void end() override;
	// 毎フレームの処理
	virtual SceneBase* update() override;
	// 描画
	virtual void draw() override;
	// シーン終了
	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;

	// 背景
	int m_fieldHandle;
	// 敵のグラフィックハンドル
	int m_enemyHandle;
	// 文字のフォントデータ
	int m_fontHandle;

	// 地面の高さ
	float m_fieldY;

	// 敵の表示位置
	Vec2 m_pos;
	// 敵のサイズ
	Vec2 m_size;
	// 敵の移動
	Vec2 m_vec;
};