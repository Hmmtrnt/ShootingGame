#include "DxLib.h"
#include "Vec2.h"
#include "player.h"
#include "game.h"
#include "SceneMain.h"
#include "Pad.h"

namespace
{
	// 自機の位置
	constexpr float kPlayerPosX = 100.0f;
	constexpr float kPlayerPosY = Game::kScreenHeight / 2;
	// 自機の速度
	constexpr float kPlayerVecY = 0.0f;

	// Y方向の速度
	constexpr float kSpeedMaxY = 8.0f;
	// ショットの発射間隔
	constexpr int kShotInterval = 70;
	// ゲージのサイズ
	constexpr int kGangeSizeX = kShotInterval;
	constexpr int kGangeSizeY = 20;
	// ゲージの表示位置
	constexpr int kGangePosX = 15;
	constexpr int kGangePosY = 70;
}

Player::Player()
{
	m_PlayerHandle = 0;
	m_pMain = nullptr;
	m_shotInterval = 0;
}
// グラフィックデータ設定
void Player::setHandle(int handle)
{
	m_PlayerHandle = handle;

	GetGraphSizeF(m_PlayerHandle, &m_size.x, &m_size.y);
}
// 初期化
void Player::init()
{
	m_pos.x = kPlayerPosX;
	m_pos.y = kPlayerPosY;
	m_vec.y = kPlayerVecY;
	m_shotInterval = 0;
	m_gangeSize.x = kGangeSizeX;
	m_gangeSize.y = kGangeSizeY;
	m_posGange.x = kGangePosX;
	m_posGange.y = kGangePosY;
}
// 毎フレームの処理
void Player::update()
{
	// パッドからの入力状態取得
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_gangeSize.x < 70)
	{
		m_gangeSize.x++;
	}
	// ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_gangeSize.x = 0;
			
			
			if (m_gangeSize.x == 70)
			{
				m_gangeSize.x = 70;
			}
			// ショットのインターバル
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}
	// 上
	if (padState & PAD_INPUT_UP)
	{
		m_pos.y -= kSpeedMaxY;
		if (m_pos.y < - 25)
		{
			m_pos.y = - 25;
		}
	}
	// 下
	else if (padState & PAD_INPUT_DOWN)
	{
		m_pos.y += kSpeedMaxY;
		if (m_pos.y > Game::kScreenHeight - 25)
		{
			m_pos.y = Game::kScreenHeight - 25;
		}
	}
}

void Player::draw()
{
	// プレイヤーの表示
	DrawTurnGraph((int)m_pos.x, (int)m_pos.y, m_PlayerHandle, true);
	DrawBox((int)m_posGange.x, (int)m_posGange.y, (int)m_posGange.x + (int)m_gangeSize.x, (int)m_posGange.y + (int)m_gangeSize.y, GetColor(0, 255, 0), true);
	DrawBox((int)m_posGange.x, (int)m_posGange.y, (int)m_posGange.x + 70, (int)m_posGange.y + 20,	GetColor(0, 0, 0), false);
	DrawString(0, 100, "インターバル", GetColor(0, 0, 0));
}