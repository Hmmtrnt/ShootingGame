#include "DxLib.h"
#include "ShotBase.h"

namespace
{
	// �\���ʒu
	constexpr float kPosX = 0.0f;
	constexpr float kPosY = 0.0f;
	// �e�̃T�C�Y
	constexpr float kSizeX = 10.0f;
	constexpr float kSizeY = 5.0f;
	// �e�̈ړ�
	constexpr float kVecX = 0.0f;
	constexpr float kVecY = 0.0f;
	// �e���o��ʒu
	constexpr float kPosShotX = 35.0f;
	constexpr float kPosShotY = 25.0f;
}

ShotBase::ShotBase()
{
	m_pos.x = kPosX;		// �\���ʒu
	m_pos.y = kPosY;
	m_size.x = kSizeX;	// �e�̃T�C�Y
	m_size.y = kSizeY;
	m_vec.x = kVecX;		// �e�̈ړ�
	m_vec.y = kVecX;

	m_isExist = false;	// �e�̗L��
}
// �V���b�g�J�n
void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	// ���@����e���o��ʒu
	pos.x += kPosShotX;		// X��
	pos.y += kPosShotY;		// Y��

	m_pos = pos;
}
// ���t���[���̏���
void ShotBase::update()
{
	if (!m_isExist) return;
}
// �`��
void ShotBase::draw()
{
	if (!m_isExist) return;
	
	DrawOval((int)m_pos.x, (int)m_pos.y, (int)m_size.x, (int)m_size.y, GetColor(0, 0, 0), true);
}