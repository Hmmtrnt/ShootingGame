#include "DxLib.h"

#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneTitle.h"

void SceneResult::init()
{
	m_isEnd = false;
}

SceneBase* SceneResult::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_2)
	{
		return (new SceneTitle);
	}
	return this;
}

void SceneResult::draw()
{
	DrawString(0, 0, "ƒŠƒUƒ‹ƒg‰æ–Ê", GetColor(255, 255, 255));
}