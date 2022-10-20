#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	
	virtual ~SceneTitle() {}
	// 初期化
	virtual void init() override;
	virtual void end() override;
	// 毎フレームの処理
	virtual SceneBase* update() override;
	// 描画
	virtual void draw() override;
	
private:
	// 背景のグラフィックハンドル
	int m_hFieldGraphic;
	// フェード処理
	int m_fadeBright;
	// フェード速度
	int m_fadeSpeed;
};