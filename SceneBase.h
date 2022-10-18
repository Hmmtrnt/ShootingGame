#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}
	// ������
	virtual void init() {}
	// �I��
	virtual void end() {}
	// ���t���[���̏���
	virtual SceneBase* update() { return this; }
	// �`��
	virtual void draw() {}
	// �V�[���I��
	virtual bool isEnd() { return false; }
};