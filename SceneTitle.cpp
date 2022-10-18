#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "Pad.h"

SceneTitle::SceneTitle()
{
	m_isEnd = false;
	m_fadeBright = 0;
	m_fadeSpeed = 0;
	m_hFieldGraphic = 0;
	m_textPosY = 0;
	m_textVecY = 0;
}

void SceneTitle::init()
{
	m_isEnd = false;
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
	m_textPosY = 0;
	m_textVecY = 4;
}

void SceneTitle::end()
{
	SetDrawBright(255, 255, 255);
	DeleteGraph(m_hFieldGraphic);
}

SceneBase* SceneTitle::update()
{
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
		if (padState & PAD_INPUT_1)
		{
			m_fadeSpeed = -8;
		}
		/*if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_fadeSpeed = -8;
			m_isEnd = true;
		}*/
	}
	
	return this;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	DrawGraph(0, 0, m_hFieldGraphic, true);
	DrawString(Game::kScreenWidth / 2 - 50, Game::kScreenHeight / 2 - 80, "やつを撃て！", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 85, Game::kScreenHeight / 2, "　　　操作説明\n１ボタン　　:発射\n左スティック:上下移動", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 125, Game::kScreenHeight / 2 + 60, "４ボタンでいつでも終了できます", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 75, Game::kScreenHeight / 2 + 130, "１ボタンでスタート", GetColor(0, 0, 0));
}