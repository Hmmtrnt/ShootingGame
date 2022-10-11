#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "ShotNormal.h"
#include "ShotBase.h"
#include <cassert>

namespace
{
	// プレイヤーの表示位置
	constexpr float kPlayerX = 100.0f;
	constexpr float kPlayerY = Game::kScreenHeight / 2;
	// 弾の表示位置
	constexpr float kShotX = 0.0f;
	constexpr float kShotY = 0.0f;
	// 楕円形のそれぞれの半径
	constexpr int kRadiusX = 5;
	constexpr int kRadiusY = 3;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{
	m_pos.x = 100.0f;
	m_pos.y = Game::kScreenHeight / 2;
	m_hPlayerGraphic = DrawCircle(m_pos.x, m_pos.y, 50, GetColor(255, 255, 255), true);
	m_hShotGraphic = DrawOval(m_pos.x, m_pos.y, kRadiusX, kRadiusY, GetColor(255, 255, 255), true);
	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);
}

void SceneMain::end()
{
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}

SceneBase* SceneMain::update()
{
	m_player.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		if (!pShot)
		{
			it++;
			continue;
		}
		pShot->update();
		if (!pShot->isExist())
		{

		}
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	/*if (padState & PAD_INPUT_2)
	{
		return (new SceneResult);
	}*/
	return this;
}

void SceneMain::draw()
{
	
	//DrawString(0, 0, "メイン画面", GetColor(255, 255, 255));
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}