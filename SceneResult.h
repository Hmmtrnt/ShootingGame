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
	// �V�[���I��
	virtual bool isEnd() { return m_isEnd; }
private:
	// �V�[���I��
	bool m_isEnd;
	// �w�i�̃O���t�B�b�N�n���h��
	int m_hFieldHandle;
	// �����̃O���t�B�b�N�n���h��
	int m_fontHandle;
};