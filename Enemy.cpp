#include "DxLib.h"
#include "Enemy.h"
#include "game.h"
#include "ShotNormal.h"

namespace
{
	// 敵の初期スピード
	constexpr int kSpeedY = 25;
	// 敵の位置座標
	constexpr float kEnemyPosX = 500.0f;
	constexpr float kEnemyPosY = Game::kScreenHeight / 2;
	// 敵の移動速度
	constexpr float kEnemyVecX = 0.0f;
	constexpr float kEnemyVecY = 0.0f;
}

Enemy::Enemy()
{
	m_speedY = 0;
	m_speedRand = 0;
	m_enemyHandle = 0;
	m_pMain = nullptr;
	m_isDead = false;
	vecY = 0;
	m_soundHandle = 0;
}

void Enemy::init()
{
	// 敵の初期スピードの変数
	m_speedY = kSpeedY;
	// 敵の位置
	m_pos.x = kEnemyPosX;
	m_pos.y = kEnemyPosY;
	// 敵の移動速度
	m_vec.x = kEnemyVecX;
	m_vec.y = kEnemyVecY;
	// スピードの代入先
	vecY = m_speedY;
	// 音のハンドル
	m_soundHandle = LoadSoundMem("sound/enemySound2.mp3");
}
// グラフィックデータ設定
void Enemy::setHandle(int handle)
{
	m_enemyHandle = handle;
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);
}
// 毎フレームの処理
void Enemy::update()
{
	// 敵のランダムな速度
	m_speedRand = GetRand(25) + 5;

	// 死亡
	if (m_isDead)	return;
	m_pos.y += vecY;
	// 画面の一番上に行った時の処理
	if (m_pos.y < -20)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
		m_speedY = m_speedRand;
		vecY = m_speedY;
	}
	// 画面の一番下に行った時の処理
	if (m_pos.y > Game::kScreenHeight - getColSize().y + 10)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
		m_speedY = m_speedRand;
		vecY = -m_speedY;
	}
}
// 敵の描画
void Enemy::draw()
{
	// 死亡
	if (m_isDead)	return;
	DrawTurnGraph((int)m_pos.x, (int)m_pos.y, m_enemyHandle, true);
}
// 敵と弾の当たり判定
bool Enemy::isCol(ShotBase& shotBase)
{
	if (isDead()) return false;
	// 弾の当たり判定
	float shotLeft = shotBase.getPos().x - shotBase.getSize().x;
	float shotRight = shotBase.getPos().x + shotBase.getSize().x;
	float shotTop = shotBase.getPos().y - shotBase.getSize().y;
	float shotBottom = shotBase.getPos().y + shotBase.getSize().y;
	// 敵の当たり判定
	float enemyLeft = getPos().x + 15;
	float enemyRight = getPos().x + getColSize().x;
	float enemyTop = getPos().y + 20;
	float enemyBottom = getPos().y + getColSize().y - 10;
	// 当たっていない処理
	if (shotLeft > enemyRight)	return false;
	if (shotRight < enemyLeft)	return false;
	if (shotTop > enemyBottom)	return false;
	if (shotBottom < enemyTop)	return false;
	// 当たった処理
	return true;
}