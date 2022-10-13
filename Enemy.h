#pragma once

#include "Vec2.h"

class SceneMain;
class ShotBase;
class ShotNormal;

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
	// �G�̎��S
	void setDead(bool isDead) { m_isDead = isDead; }

	// �����蔻��
	bool isCol(ShotBase& shotBase);

	// ���擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getColSize() const { return m_colSize; }


private:
	// �G�̃X�s�[�h
	int m_speedY;
	// �G�̃X�s�[�h�̐U�ꕝ
	int m_speedRand;
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �G�̑���
	int vecY;

	// ����
	bool m_isDead;

	// SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
	// �����蔻��̕��ƍ���
	Vec2 m_colSize;
};