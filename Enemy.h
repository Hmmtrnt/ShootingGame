#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }
	// �G�̏�����
	void init();
	// SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// �G�̏���
	void update();
	// �`��
	void draw();

	// ���擾
	Vec2 getPos() const { return m_pos; }

private:
	// �O���t�B�b�N�n���h��
	int m_handle;
	//
	int vecY;
	// SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
};