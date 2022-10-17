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

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;

	// �w�i�̃O���t�B�b�N�n���h��
	int m_hFieldGraphic;
	// �t�F�[�h����
	int m_fadeBright;
	// �t�F�[�h���x
	int m_fadeSpeed;
	// �w�i�̃O���t�B�b�N�n���h��
	int m_fieldHandle;
	// �e�L�X�g�\���ʒu�ύX
	int m_textPosY;
	int m_textVecY;
};