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
	// �t�F�[�h����
	int m_fadeBright;
	// �t�F�[�h���x
	int m_fadeSpeed;
	// �w�i�̃O���t�B�b�N�n���h��
	int m_fieldHandle;
};