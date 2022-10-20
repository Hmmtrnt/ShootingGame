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
	// フェード
	constexpr int kFadeBright = 0;		// 処理
	constexpr int kFadeSpeed = 5;		// 速度
	// 描画輝度
	constexpr int kRedBright = 255;		// 赤
	constexpr int kGreenBright = 255;	// 緑
	constexpr int kBlueBright = 255;	// 青
}

SceneResult::SceneResult()
{
	m_hFieldHandle = 0;		// 背景
	m_fontHandle = 0;		// フォント
	m_fadeBright = 0;		// フェード処理
	m_fadeSpeed = 0;		// フェード速度
	m_input1 = 0;			// 入力情報１
	m_input2 = 0;			// 入力情報２
}
// 初期化
void SceneResult::init()
{
	// 背景データ
	m_hFieldHandle = LoadGraph("data/field2.jpg");
	// フォントデータ
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);
	m_fadeBright = kFadeBright;	// フェード処理
	m_fadeSpeed = kFadeSpeed;	// フェード速度
	m_input1 = 0;			// 入力情報１
	m_input2 = 0;			// 入力情報２
}
// 終了
void SceneResult::end()
{
	// 描画輝度
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
	// グラフィックメモリ消去
	DeleteGraph(m_hFieldHandle);
	DeleteFontToHandle(m_fontHandle);
}
// 毎フレームの処理
SceneBase* SceneResult::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// フェードアウトの処理
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_input1 > 0)
	{
		m_fadeBright = 0;
		return(new SceneTitle);
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_input2 > 0)
	{
		m_fadeBright = 0;
		return(new SceneMain);
	}

	if (m_fadeSpeed == 0)
	{
		// フェードアウト開始
		if (padState & PAD_INPUT_1 || padState & PAD_INPUT_2)
		{
			m_fadeSpeed = -kFadeSpeed;
		}
	}

	if (padState & PAD_INPUT_1)
	{
		m_input1++;
	}
	if (padState & PAD_INPUT_2)
	{
		m_input2++;
	}

	//int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (padState & PAD_INPUT_1)
	//{
	//	return (new SceneTitle);
	//}
	//if (padState & PAD_INPUT_2)
	//{
	//	return (new SceneMain);
	//}
	//
	return this;
}
// 描画
void SceneResult::draw()
{
	// 描画輝度
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// 背景
	DrawGraph(0, 0, m_hFieldHandle, true);
	// 文字
	DrawStringToHandle(Game::kScreenWidth / 2 - 170, Game::kScreenHeight / 2 - 100, "ＧＡＭＥＣＬＥＡＲ", GetColor(0, 0, 0), m_fontHandle);
	DrawFormatString(Game::kScreenWidth / 2 - 140, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "主人公「これで安心して過ごせそうだ」");
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "１ボタン:　タイトル", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "２ボタン:リスタート", GetColor(0, 0, 0));
}