#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneFail.h"
#include "ShotNormal.h"
#include "ShotBase.h"
#include <cassert>

namespace
{
	// プレイヤーの表示位置
	constexpr float kPosPlayerX = 100.0f;
	constexpr float kPosPlayerY = Game::kScreenHeight / 2;
	// 弾の表示位置
	constexpr float kPosShotX = 0.0f;
	constexpr float kPosShotY = 0.0f;
	// 弾の幅
	constexpr float kSizeShotX = 10.0f;
	constexpr float kSizeShotY = 10.0f;
	// 敵の位置
	constexpr float kPosEnemyX = 540.0f;
	constexpr float kPosEnemyY = Game::kScreenWidth / 2;
	// 敵の幅
	constexpr float kSizeEnemyX = 30.0f;
	constexpr float kSizeEnemyY = 30.0f;
	// フォント
	constexpr int kSizeFont = 50;	// サイズ
	constexpr int kThickFont = 4;	// 太さ
	// 敵の数
	constexpr int kEnemyNum = 1;
	// 弾の数
	constexpr int kShotNum = 3;
	// 時間
	constexpr int kTime = 40;
	// フェード
	constexpr int kFadeBright = 0;		// 処理
	constexpr int kFadeSpeed = 5;		// 速度
	// 描画輝度
	constexpr int kRedBright = 255;		// 赤
	constexpr int kGreenBright = 255;	// 緑
	constexpr int kBlueBright = 255;	// 青
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = 0;		// プレイヤーのグラフィックハンドル
	m_hShotGraphic = 0;			// ショットのグラフィックハンドル
	m_hFieldGraphic = 0;		// 背景のグラフィックハンドル
	m_hEnemyGraphic = 0;		// 敵のグラフィックハンドル
	m_fontHandle = 0;			// 文字のハンドル
	m_enemyNum = 0;				// 敵の数
	m_shotNum = 0;				// 弾の数
	m_time = 0;					// 最後の一発を撃ち終わってからゲームオーバーまでの時間
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
// 初期化
void SceneMain::init()
{

	/*表示位置*/
	// プレイヤー
	m_posPlayer.x = kPosPlayerX;
	m_posPlayer.y = kPosPlayerY;
	// 弾
	m_posShot.x = kPosShotX;
	m_posShot.y = kPosShotY;
	// 弾の幅
	m_sizeShot.x = kSizeShotX;
	m_sizeShot.y = kSizeShotY;
	// 敵
	m_posEnemy.x = kPosEnemyX;
	m_posEnemy.y = kPosEnemyY;
	// 敵の幅
	m_sizeEnemy.x = kSizeEnemyX;
	m_sizeEnemy.y = kSizeEnemyY;
	// プレイヤー
	m_hPlayerGraphic = LoadGraph("data/player2.png");
	// 弾
	m_hShotGraphic = DrawBox((int)m_posShot.x, (int)m_posShot.y, (int)m_posShot.x + (int)m_sizeShot.x, (int)m_posShot.y + (int)m_sizeShot.y, GetColor(255, 255, 255), true);
	// 背景
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
	// 敵
	m_hEnemyGraphic = LoadGraph("data/enemy2.png");
	// 文字
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);
	// 敵の数
	m_enemyNum = kEnemyNum;
	// 弾の数
	m_shotNum = kShotNum;
	// 時間
	m_time = kTime;
	// フェード
	m_fadeBright = kFadeBright;	// 処理
	m_fadeSpeed = kFadeSpeed;	// 速度

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
	DeleteFontToHandle(m_fontHandle);
	// 描画輝度
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
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

	// フェードアウトの処理
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_enemyNum == 0)
	{
		m_fadeBright = 0;
		return(new SceneResult);
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_time == 0)
	{
		m_fadeBright = 0;
		return(new SceneFail);
	}

	if (m_fadeSpeed == 0)
	{
		// フェードアウト開始
		if (m_enemyNum == 0)
		{
			m_fadeSpeed = -5;
		}
		if (m_shotNum == 0)
		{
			m_time--;
			if (m_time == 0)
			{
				m_fadeSpeed = -5;
			}
		}
	}

	return this;
}

void SceneMain::draw()
{
	// 描画輝度
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
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
	// 時間確認
	DrawFormatString(0, 50, GetColor(0, 0, 0), "時間:%d", m_time);
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