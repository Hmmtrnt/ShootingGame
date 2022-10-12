#include "DxLib.h"

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
		// Main�ɐ؂�ւ�
		return(new SceneMain);
	}
	
	return this;
}

void SceneTitle::draw()
{
	DrawString(0, 0, "�^�C�g�����", GetColor(255, 255, 255));
}