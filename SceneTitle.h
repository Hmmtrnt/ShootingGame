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

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;

	// 背景のグラフィックハンドル
	int m_hFieldGraphic;
	// フェード処理
	int m_fadeBright;
	// フェード速度
	int m_fadeSpeed;
	// 背景のグラフィックハンドル
	int m_fieldHandle;
	// テキスト表示位置変更
	int m_textPosY;
	int m_textVecY;
};