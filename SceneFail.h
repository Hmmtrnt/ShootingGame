#pragma once
#include "SceneBase.h"

class SceneFail : public SceneBase
{
public:
	SceneFail();
	virtual ~SceneFail() {}
	// ������
	virtual void init() override;
	// �I��
	virtual void end() override;
	// ���t���[���̏���
	virtual SceneBase* update() override;
	// �`��
	virtual void draw() override;
	
private:
	// �w�i
	int m_fieldHandle;
	// �G�̃O���t�B�b�N�n���h��
	int m_enemyHandle;
	// �����̃t�H���g�f�[�^
	int m_fontHandle;
	// �t�F�[�h����
	int m_fadeBright;
	// �t�F�[�h���x
	int m_fadeSpeed;
	// ���͏��
	int m_input1;
	int m_input2;

	// �n�ʂ̍���
	float m_fieldY;

	// �G�̕\���ʒu
	Vec2 m_pos;
	// �G�̃T�C�Y
	Vec2 m_size;
	// �G�̈ړ�
	Vec2 m_vec;
};