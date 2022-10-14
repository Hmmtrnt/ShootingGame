#pragma once
#include "SceneBase.h"

class SceneFail : public SceneBase
{
public:
	SceneFail();
	
	virtual ~SceneFail() {}

	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	bool m_isEnd;

	// �w�i
	int m_fieldHandle;
	// �G�̃O���t�B�b�N�n���h��
	int m_enemyHandle;

	// �n�ʂ̍���
	float m_fieldY;

	// �G�̕\���ʒu
	Vec2 m_pos;
	// �G�̃T�C�Y
	Vec2 m_size;
	// �G�̈ړ�
	Vec2 m_vec;
};