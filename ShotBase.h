#pragma once
#include "Vec2.h"

class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	void setHandle(int handle) {}

	// �V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();

	// ���݂��邩�ǂ���
	bool isExist() const { return m_isExist; }

	// ���擾
	Vec2 getPos() const { return m_pos; }
	Vec2 getSize() const { return m_size; }

protected:
	// �\���ʒu
	Vec2 m_pos;
	// �e�̕�
	Vec2 m_size;
	// �ړ�
	Vec2 m_vec;
	// ���݂��邩�ǂ���
	bool m_isExist;
};