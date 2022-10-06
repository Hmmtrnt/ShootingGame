#include "DxLib.h"

#include "SceneMain.h"
#include "SceneTitle.h"

void SceneMain::init()
{

}

SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_3)
	{
		return (new SceneTitle);
	}
	return this;
}

void SceneMain::draw()
{
	DrawString(0, 0, "ƒƒCƒ“‰æ–Ê", GetColor(255, 255, 255));
}