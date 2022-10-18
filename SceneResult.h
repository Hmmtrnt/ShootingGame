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
	// シーン終了
	virtual bool isEnd() { return m_isEnd; }
private:
	// シーン終了
	bool m_isEnd;
	// 背景のグラフィックハンドル
	int m_hFieldHandle;
	// 文字のグラフィックハンドル
	int m_fontHandle;
};