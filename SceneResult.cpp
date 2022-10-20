#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneTitle.h"

namespace
{
	// フォント
	constexpr int kSizeFont = 40;	// サイズ
	constexpr int kThickFont = 3;	// 太さ
}

SceneResult::SceneResult()
{
	m_hFieldHandle = 0;		// 背景
	m_fontHandle = 0;		// フォント
}
// 初期化
void SceneResult::init()
{
	// 背景データ
	m_hFieldHandle = LoadGraph("data/field2.jpg");
	// フォントデータ
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);
}
// 終了
void SceneResult::end()
{
	// グラフィックメモリ消去
	DeleteGraph(m_hFieldHandle);
	DeleteFontToHandle(m_fontHandle);
}
// 毎フレームの処理
SceneBase* SceneResult::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		return (new SceneTitle);
	}
	if (padState & PAD_INPUT_2)
	{
		return (new SceneMain);
	}
	
	return this;
}
// 描画
void SceneResult::draw()
{
	// 背景
	DrawGraph(0, 0, m_hFieldHandle, true);
	// 文字
	DrawStringToHandle(Game::kScreenWidth / 2 - 170, Game::kScreenHeight / 2 - 100, "ＧＡＭＥＣＬＥＡＲ", GetColor(0, 0, 0), m_fontHandle);
	DrawFormatString(Game::kScreenWidth / 2 - 140, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "主人公「これで安心して過ごせそうだ」");
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "１ボタン:　タイトル", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "２ボタン:リスタート", GetColor(0, 0, 0));
}