#include "DxLib.h"
#include "Vec2.h"
#include "player.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// Y方向の速度
	constexpr float kSpeedMaxY = 8.0f;
	// ショットの発射間隔
	constexpr int kShotInterval = 70;
}

Player::Player()
{
	m_Playerhandle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
	
}

Player::~Player()
{

}
// グラフィックデータ設定
void Player::setHandle(int handle)
{
	m_Playerhandle = handle;

	GetGraphSizeF(m_Playerhandle, &m_size.x, &m_size.y);
}
// 初期化
void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = Game::kScreenHeight / 2;
	m_vec.y = 0.0f;
	m_shotInterval = 0;
	
}
// 毎フレームの処理
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
	DrawTurnGraph(m_pos.x, m_pos.y, m_Playerhandle, true);
}