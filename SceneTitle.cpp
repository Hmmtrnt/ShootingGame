#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"

void SceneTitle::init()
{
	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_4)
	{
		// Mainに切り替え
		return(new SceneMain);
	}
	
	return this;
}

void SceneTitle::draw()
{
	DrawString(Game::kScreenWidth / 2 - 50, Game::kScreenHeight / 2 - 50, "やつを打て！", GetColor(255, 255, 255));
}