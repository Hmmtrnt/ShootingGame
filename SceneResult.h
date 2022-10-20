#pragma once
#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult() {}
	// 初期化
	virtual void init() override;
	// 終了
	virtual void end() override;
	// 毎フレームの処理
	virtual SceneBase* update() override;
	// 描画
	virtual void draw() override;
	
private:
	
	// 背景のグラフィックハンドル
	int m_hFieldHandle;
	// 文字のグラフィックハンドル
	int m_fontHandle;
	// フェード処理
	int m_fadeBright;
	// フェード速度
	int m_fadeSpeed;
	// 入力情報
	int m_input1;
	int m_input2;
};