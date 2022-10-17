#include "DxLib.h"

#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneTitle.h"

SceneResult::SceneResult()
{
	m_isEnd = false;
	m_hFieldHandle = 0;
}

void SceneResult::init()
{
	m_isEnd = false;
	m_hFieldHandle = LoadGraph("data/field2.jpg");
}

void SceneResult::end()
{
	DeleteGraph(m_hFieldHandle);
}

SceneBase* SceneResult::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		return (new SceneTitle);
	}
	return this;
}

void SceneResult::draw()
{
	DrawGraph(0, 0, m_hFieldHandle, true);
	DrawString(0, 0, "ƒŠƒUƒ‹ƒg‰æ–Ê", GetColor(0, 0, 0));
}