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
	m_hPlayerGraphic = 0;		// プレイヤーのグラフィックハンドル
	m_hShotGraphic = 0;		// ショットのグラフィックハンドル
	m_hFieldGraphic = 0;		// 背景のグラフィックハンドル
	m_hEnemyGraphic = 0;		// 敵のグラフィックハンドル
	m_fontHandle = 0;			// 文字のハンドル
	m_enemyNum = 0;				// 敵の数
	m_shotNum = 0;				// 弾の数
	m_time = 0;					// 最後の一発を撃ち終わってからゲームオーバーまでの時間
}
// 初期化
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
	// 文字
	m_fontHandle = CreateFontToHandle(NULL, 50, 4);
	// 敵の数
	m_enemyNum = 1;
	// 弾の数
	m_shotNum = 3;
	// 時間
	m_time = 50;

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);

	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}
// 終了
void SceneMain::end()
{
	// グラフィックメモリ削除
	DeleteGraph(m_hFieldGraphic);
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphic);
	// 確認処理
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}
// 毎フレームの処理
SceneBase* SceneMain::update()
{
	m_enemy.update();
	m_player.update();
	// ベクター処理
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
			m_enemyNum--;
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
	if (m_enemyNum == 0)
	{
		return (new SceneResult);
	}
	else if (m_shotNum == 0)
	{
		// 弾をすべて撃ち終わったら時間が減りゲームオーバー画面へ
		m_time--;
		if (m_time == 0)
		{
			return (new SceneFail);
		}
	}
	return this;
}

void SceneMain::draw()
{
	// 背景
	DrawGraph(0, 0, m_hFieldGraphic, false);
	m_enemy.draw();		// 敵
	m_player.draw();	// 自機
	// 弾
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;
		pShot->draw();
	}
	// 弾数表示
	DrawFormatStringFToHandle(0, 0, GetColor(0, 0, 0), m_fontHandle, "弾:%d", m_shotNum);
}
// 弾の生成
bool SceneMain::createShotNormal(Vec2 pos)
{
	// 弾の生成と消去をそれぞれ確認する
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);
	m_shotNum--;	// 弾数減少

	return true;
}