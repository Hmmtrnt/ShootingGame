#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}
	// 初期化
	virtual void init() {}
	// 終了
	virtual void end() {}
	// 毎フレームの処理
	virtual SceneBase* update() { return this; }
	// 描画
	virtual void draw() {}
};