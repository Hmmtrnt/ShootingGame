#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"

SceneTitle::SceneTitle()
{
	// 背景のグラフィックハンドル
	m_hFieldGraphic = 0;
	// フェード処理
	m_fadeBright = 0;
	// フェード速度
	m_fadeSpeed = 0;
	// 背景のグラフィックハンドル
	m_fieldHandle = 0;
}

void SceneTitle::init()
{
	// フェード処理
	m_fadeBright = 0;
	// フェード速度
	m_fadeSpeed = 5;
	// 背景
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
}

void SceneTitle::end()
{
	// 描画輝度
	SetDrawBright(255, 255, 255);
	// グラフィックメモリから削除
	DeleteGraph(m_hFieldGraphic);
}

SceneBase* SceneTitle::update()
{
	// フェードアウトの処理
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		m_fadeBright = 0;
		return(new SceneMain);
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)
	{
		// フェードアウト開始
		if (padState & PAD_INPUT_1)
		{
			m_fadeSpeed = -5;
		}
	}
	
	return this;
}

void SceneTitle::draw()
{
	// 描画輝度
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// 背景
	DrawGraph(0, 0, m_hFieldGraphic, true);
	DrawString(Game::kScreenWidth / 2 - 50, Game::kScreenHeight / 2 - 80, "やつを撃て！", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 85, Game::kScreenHeight / 2, "　　　操作説明\n１ボタン　　:発射\n左スティック:上下移動", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 125, Game::kScreenHeight / 2 + 60, "４ボタンでいつでも終了できます", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 75, Game::kScreenHeight / 2 + 130, "１ボタンでスタート", GetColor(0, 0, 0));
}