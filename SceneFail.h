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
	
private:
	// 背景
	int m_fieldHandle;
	// 敵のグラフィックハンドル
	int m_enemyHandle;
	// 文字のフォントデータ
	int m_fontHandle;
	// フェード処理
	int m_fadeBright;
	// フェード速度
	int m_fadeSpeed;
	// 入力情報
	int m_input1;
	int m_input2;

	// 地面の高さ
	float m_fieldY;

	// 敵の表示位置
	Vec2 m_pos;
	// 敵のサイズ
	Vec2 m_size;
	// 敵の移動
	Vec2 m_vec;
};