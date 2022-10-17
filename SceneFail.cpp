#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneFail.h"
#include "SceneTitle.h"

namespace
{
	// “G‚ÌƒWƒƒƒ“ƒv—Í
	constexpr float kJumpEnemy = -15.0f;
	// “G‚Ìd—Í
	constexpr float kGravity = 1.0f;
}

SceneFail::SceneFail()
{
	m_isEnd = false;
	m_fieldHandle = 0;
	m_enemyHandle = 0;
	m_fontHandle = 0;
	m_pos.x = 0;
	m_pos.y = 0;
	m_vec.x = 0;
	m_vec.y = 0;
	m_size.x = 0;
	m_size.y = 0;
	m_fieldY = 400;
}


void SceneFail::init()
{
	m_isEnd = false;
	m_enemyHandle = LoadGraph("data/enemy2.png");
	m_fieldHandle = LoadGraph("data/field2.jpg");
	m_fontHandle = CreateFontToHandle(NULL, 40, 3);
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);

	m_pos.x = 80;
	m_pos.y = m_fieldY;
}

void SceneFail::end()
{
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_fieldHandle);
}

SceneBase* SceneFail::update()
{
	m_pos += m_vec;
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (isField)
	{
		m_vec.y = kJumpEnemy;
	}
	m_vec.y += kGravity;

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		return (new SceneTitle);
	}
	return this;
}

void SceneFail::draw()
{
	DrawGraphF(0, 0, m_fieldHandle, true);
	DrawFormatString(Game::kScreenWidth / 2 - 120, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "‚â‚ÂuƒIƒŒ‚Í¶‚«c‚Á‚½‚¼Iv");
	DrawStringToHandle(Game::kScreenWidth / 2 - 160, Game::kScreenHeight / 2 - 100, "‚f‚`‚l‚d‚n‚u‚d‚q", GetColor(255, 0, 0), m_fontHandle);
	DrawGraphF(m_pos.x, m_pos.y, m_enemyHandle, true);
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "‚Pƒ{ƒ^ƒ“:ƒ^ƒCƒgƒ‹‰æ–Ê", GetColor(0, 0, 0));
	
}