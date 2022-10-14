#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneFail.h"
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
	constexpr int kRadiusX = 7;
	constexpr int kRadiusY = 4;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
	m_hFieldGraphic = -1;
	m_hEnemyGraphic = -1;
	enemyNum = 0;
	shotNum = 0;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{

	/*表示位置*/
	// プレイヤー
	m_posPlayer.x = 100.0f;
	m_posPlayer.y = Game::kScreenHeight / 2;
	// 弾
	m_posShot.x = 0.0f;
	m_posShot.y = 0.0f;
	// 弾の幅
	m_sizeShot.x = 10.0f;
	m_sizeShot.y = 10.0f;
	// 敵
	m_posEnemy.x = 540.0f;
	m_posEnemy.y = Game::kScreenWidth / 2;
	// 敵の幅
	m_sizeEnemy.x = 30.0f;
	m_sizeEnemy.y = 30.0f;
	// プレイヤー
	m_hPlayerGraphic = LoadGraph("data/player2.png");
	// 弾
	m_hShotGraphic = DrawBox(m_posShot.x, m_posShot.y, m_posShot.x + m_sizeShot.x, m_posShot.y + m_sizeShot.y, GetColor(255, 255, 255), true);
	// 背景
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
	// 敵
	m_hEnemyGraphic = LoadGraph("data/enemy2.png");
	// 敵の数
	enemyNum = 1;
	// 弾の数
	shotNum = 5;
	// 時間
	time = 90;

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);

	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}

void SceneMain::end()
{
	DeleteGraph(m_hFieldGraphic);
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphic);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}

SceneBase* SceneMain::update()
{
	m_enemy.update();
	m_player.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		// 弾発射した時の処理
		auto& pShot = (*it);
		if (!pShot)
		{
			
			it++;
			continue;
		}
		pShot->update();
		// 敵の当たり判定
		if (m_enemy.isCol(*pShot))
		{
			m_enemy.setDead(true);
			enemyNum--;
		}
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;
			// vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}

	// シーン移動(予定では敵に弾が当たったらリザルト)
	if (enemyNum == 0)
	{
		return (new SceneResult);
	}
	else if (shotNum == 0)
	{
		time--;
		if (time == 0)
		{
			return (new SceneFail);
		}
	}
	return this;
}

void SceneMain::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	m_enemy.draw();
	m_player.draw();
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;
		pShot->draw();
	}

	DrawFormatString(0, 20, GetColor(0, 0, 0), "やつ%d", enemyNum);
	DrawString(0, 0, "メイン画面", GetColor(0, 0, 0));
	DrawFormatString(0, 40, GetColor(0, 0, 0), "弾:%d", shotNum);
	DrawFormatString(0, 60, GetColor(0, 0, 0), "時間:%d", time);
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);
	shotNum--;

	return true;
}