#include "DxLib.h"
#include "Vec2.h"
#include "player.h"
#include "game.h"
#include "SceneMain.h"
#include "Pad.h"

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
	// �Q�[�W�̃T�C�Y
	constexpr int kGangeSizeX = kShotInterval;
	constexpr int kGangeSizeY = 20;
	// �Q�[�W�̕\���ʒu
	constexpr int kGangePosX = 15;
	constexpr int kGangePosY = 70;
}

Player::Player()
{
	m_PlayerHandle = 0;
	m_pMain = nullptr;
	m_shotInterval = 0;
}
// �O���t�B�b�N�f�[�^�ݒ�
void Player::setHandle(int handle)
{
	m_PlayerHandle = handle;

	GetGraphSizeF(m_PlayerHandle, &m_size.x, &m_size.y);
}
// ������
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
// ���t���[���̏���
void Player::update()
{
	// �p�b�h����̓��͏�Ԏ擾
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_gangeSize.x < 70)
	{
		m_gangeSize.x++;
	}
	// �V���b�g��������
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
	DrawTurnGraph((int)m_pos.x, (int)m_pos.y, m_PlayerHandle, true);
	DrawBox((int)m_posGange.x, (int)m_posGange.y, (int)m_posGange.x + (int)m_gangeSize.x, (int)m_posGange.y + (int)m_gangeSize.y, GetColor(0, 255, 0), true);
	DrawBox((int)m_posGange.x, (int)m_posGange.y, (int)m_posGange.x + 70, (int)m_posGange.y + 20,	GetColor(0, 0, 0), false);
	DrawString(0, 100, "�C���^�[�o��", GetColor(0, 0, 0));
}