#pragma once
#include "SceneBase.h"

class SceneResult : public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult() {}
	// ������
	virtual void init() override;
	// �I��
	virtual void end() override;
	// ���t���[���̏���
	virtual SceneBase* update() override;
	// �`��
	virtual void draw() override;
	
private:
	
	// �w�i�̃O���t�B�b�N�n���h��
	int m_hFieldHandle;
	// �����̃O���t�B�b�N�n���h��
	int m_fontHandle;
	// �t�F�[�h����
	int m_fadeBright;
	// �t�F�[�h���x
	int m_fadeSpeed;
	// ���͏��
	int m_input1;
	int m_input2;
};