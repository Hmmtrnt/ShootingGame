#include "game.h"
#include "ShotNormal.h"
#include "SceneResult.h"

namespace
{
	// �e�̃X�s�[�h
	constexpr float kShotSpeed = 25.0f;
}
// �V���b�g�J�n
void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);
	// �e�̋O��
	m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;
}
// ���t���[���̏���
void ShotNormal::update()
{
	if (!m_isExist) return;
	m_pos += m_vec;
	// ��ʊO�ɏo���������
	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}