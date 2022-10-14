#include "DxLib.h"

#include "SceneMain.h"
#include "SceneFail.h"
#include "SceneTitle.h"

void SceneFail::init()
{
	m_isEnd = false;
}

SceneBase* SceneFail::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_3)
	{
		return (new SceneTitle);
	}
	return this;
}

void SceneFail::draw()
{
	DrawString(0, 0, "Ž¸”s‰æ–Ê", GetColor(255, 255, 255));
}