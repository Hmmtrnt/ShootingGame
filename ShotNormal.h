#pragma once

#include "Enemy.h"
#include "ShotBase.h"

class ShotNormal : public ShotBase
{
public:
	ShotNormal() {}
	virtual ~ShotNormal() {}

	// �V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

	// �G�l�~�[�Ƃ̏Փ˔���
	bool isCol(Enemy& enemy);

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getGraphSize() const { return m_graphSize; }
	Vec2 getColSize() const { return m_colSize; }

private:
	// �O���t�B�b�N�̕��ƍ���
	Vec2 m_graphSize;
	// �����蔻��̕��ƍ���
	Vec2 m_colSize;
};