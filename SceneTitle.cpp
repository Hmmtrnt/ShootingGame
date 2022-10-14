#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"

SceneTitle::SceneTitle()
{
	m_isEnd = false;
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}

void SceneTitle::init()
{
	m_isEnd = false;
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}

void SceneTitle::end()
{
	SetDrawBright(255, 255, 255);
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
	}
	
	return this;
}

void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	DrawString(Game::kScreenWidth / 2 - 50, Game::kScreenHeight / 2 - 80, "やつを打て！", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 85, Game::kScreenHeight / 2 - 0, "　　　操作説明\n１ボタン　　:発射\n左スティック:上下移動", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 75, Game::kScreenHeight / 2 + 130, "１ボタンでスタート", GetColor(255, 255, 255));
}