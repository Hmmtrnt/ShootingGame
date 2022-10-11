#include "DxLib.h"
#include "Vec2.h"
#include "player.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// Y方向の速度
	constexpr float kSpeedMaxY = 8.0f;
	constexpr float kAcc = 0.4f;
	// ショットの発射間隔
	constexpr int kShotInterval = 30;
}

Player::Player()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
	m_radius = 50;
}

Player::~Player()
{

}

void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = Game::kScreenHeight / 2;
	m_vec.y = 0.0f;
	m_shotInterval = 0;
	m_radius = 50;
}

void Player::update()
{
	// パッドからの入力状態取得
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotNormal(getPos()))
			{

			}
		}
	}
}

void Player::draw()
{
	// 仮自機
	DrawCircle(m_pos.x, m_pos.y, 50, GetColor(255, 255, 255), true);
}