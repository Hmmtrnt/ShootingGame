#include "DxLib.h"
#include "ShotBase.h"

ShotBase::ShotBase()
{
	m_pos.x = 0.0f;		// �\���ʒu
	m_pos.y = 0.0f;
	m_size.x = 10.0f;	// �e�̃T�C�Y
	m_size.y = 5.0f;
	m_vec.x = 0.0f;		// �e�̈ړ�
	m_vec.y = 0.0f;

	m_isExist = false;	// �e�̗L��
}
// �V���b�g�J�n
void ShotBase::start(Vec2 pos)
{
	m_isExist = true;
	// ���@����e���o��ʒu
	pos.x += 35.0f;		// X��
	pos.y += 25.0f;		// Y��

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
	
	DrawOval(m_pos.x, m_pos.y, m_size.x, m_size.y, GetColor(0, 0, 0), true);
}