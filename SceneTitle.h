#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	
	virtual ~SceneTitle() {}
	// ������
	virtual void init() override;
	virtual void end() override;
	// ���t���[���̏���
	virtual SceneBase* update() override;
	// �`��
	virtual void draw() override;
	
private:
	// �w�i�̃O���t�B�b�N�n���h��
	int m_hFieldGraphic;
	// �t�F�[�h����
	int m_fadeBright;
	// �t�F�[�h���x
	int m_fadeSpeed;
};