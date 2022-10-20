#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneFail.h"
#include "SceneTitle.h"
#include "Pad.h"

namespace
{
	// 敵の位置
	constexpr int kPosEnemy = 80;
	// 地面の高さ
	constexpr int kFieldY = 400;
	// フォント
	constexpr int kSizeFont = 40;	// サイズ
	constexpr int kThickFont = 3;	// 太さ
	// 敵のジャンプ力
	constexpr float kJumpEnemy = -15.0f;
	// 敵の重力
	constexpr float kGravity = 1.0f;
	// フェード
	constexpr int kFadeBright = 0;		// 処理
	constexpr int kFadeSpeed = 5;		// 速度
	// 描画輝度
	constexpr int kRedBright = 255;		// 赤
	constexpr int kGreenBright = 255;	// 緑
	constexpr int kBlueBright = 255;	// 青
}

SceneFail::SceneFail()
{
	m_fieldHandle = 0;	// 背景
	m_enemyHandle = 0;	// 敵
	m_fontHandle = 0;	// 文字
	m_fadeBright = 0;	// フェード処理
	m_fadeSpeed = 0;	// フェード速度
	m_input1 = 0;		// 入力情報１
	m_input2 = 0;		// 入力情報２
	m_pos.x = 0;		// 表示位置
	m_pos.y = 0;
	m_vec.x = 0;		// 移動速度
	m_vec.y = 0;
	m_size.x = 0;		// サイズ
	m_size.y = 0;
	m_fieldY = kFieldY;		// 地面の高さ
}


void SceneFail::init()
{
	m_enemyHandle = LoadGraph("data/enemy2.png");		// 敵
	m_fieldHandle = LoadGraph("data/field2.jpg");		// 背景
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);		// 文字
	m_fadeBright = kFadeBright;	// フェード処理
	m_fadeSpeed = kFadeSpeed;	// フェード速度
	m_input1 = 0;			// 入力情報１
	m_input2 = 0;			// 入力情報２
	
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);	// 敵のサイズ

	m_pos.x = kPosEnemy;		// 敵のX座標
	m_pos.y = m_fieldY;	// 敵のY座標
}
// 終了
void SceneFail::end()
{
	// グラフィックメモリの消去
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_fieldHandle);
	DeleteFontToHandle(m_fontHandle);
	// 描画輝度
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
}
// 毎フレームの処理
SceneBase* SceneFail::update()
{
	m_pos += m_vec;
	// 地面判定
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}
	// ジャンプ処理
	if (isField)
	{
		// ジャンプ
		m_vec.y = kJumpEnemy;
	}
	// 重力
	m_vec.y += kGravity;

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
		if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
		{
			m_fadeSpeed = -kFadeSpeed;
		}
	}

	if (m_fadeBright == 255)
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_input1++;
		}
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_input2++;
		}
	}
	

	return this;
}

void SceneFail::draw()
{
	// 描画輝度
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// 背景
	DrawGraphF(0, 0, m_fieldHandle, true);
	// テキスト
	DrawFormatString(Game::kScreenWidth / 2 - 120, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "やつ「オレは生き残ったぞ！」");
	DrawStringToHandle(Game::kScreenWidth / 2 - 160, Game::kScreenHeight / 2 - 100, "ＧＡＭＥＯＶＥＲ", GetColor(255, 0, 0), m_fontHandle);
	DrawGraphF(m_pos.x, m_pos.y, m_enemyHandle, true);
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "１ボタン:　タイトル", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "２ボタン:リスタート", GetColor(0, 0, 0));
}