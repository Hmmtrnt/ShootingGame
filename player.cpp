#include "DxLib.h"
#include "Vec2.h"
#include "player.h"
#include "game.h"
#include "SceneMain.h"

namespace
{
	// ���@�̈ʒu
	constexpr float kPlayerPosX = 100.0f;
	constexpr float kPlayerPosY = Game::kScreenHeight / 2;
	// ���@�̑��x
	constexpr float kPlayerVecY = 0.0f;

	// Y�����̑��x
	constexpr float kSpeedMaxY = 8.0f;
	// �V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 70;
}

Player::Player()
{
	m_Playerhandle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
	
}
// �O���t�B�b�N�f�[�^�ݒ�
void Player::setHandle(int handle)
{
	m_Playerhandle = handle;

	GetGraphSizeF(m_Playerhandle, &m_size.x, &m_size.y);
}
// ������
void Player::init()
{
	m_pos.x = kPlayerPosX;
	m_pos.y = kPlayerPosY;
	m_vec.y = kPlayerVecY;
	m_shotInterval = 0;
	
}
// ���t���[���̏���
void Player::update()
{
	// �p�b�h����̓��͏�Ԏ擾
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �V���b�g��������
	m_shotInterval--;
	if (m_shotInterval < 0) m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			// �V���b�g�̃C���^�[�o��
			if (m_pMain->createShotNormal(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}
	// ��
	if (padState & PAD_INPUT_UP)
	{
		m_pos.y -= kSpeedMaxY;
		if (m_pos.y < - 25)
		{
			m_pos.y = - 25;
		}
	}
	// ��
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
	// �v���C���[�̕\��
	DrawTurnGraph((int)m_pos.x, (int)m_pos.y, m_Playerhandle, true);
}