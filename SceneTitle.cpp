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
		// Main‚ÉØ‚è‘Ö‚¦
		return(new SceneMain);
	}
	
	return this;
}

void SceneTitle::draw()
{
	DrawString(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 - 50, "‚â‚Â‚ğ‘Å‚¿”²‚¯I", GetColor(255, 255, 255));
}