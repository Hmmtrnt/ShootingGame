#pragma once

#include <vector>
#include "player.h"
#include "SceneBase.h"
#include "ShotBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	
	virtual ~SceneMain();

	// ������
	virtual void init();
	// �I������
	virtual void end();

	// ���t���[������
	virtual SceneBase* update() override;

	// ���t���[���`��
	virtual void draw() override;

	// �e�̐���
	bool createShotNormal(Vec2 pos);
private:
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic;
	int m_hShotGraphic;
	// �G�̃O���t�B�b�N�n���h��
	int m_hEnemyGraphic;

	// �v���C���[
	Player m_player;
	// �V���b�g
	std::vector<ShotBase*>m_pShotVt;
	// �\���ʒu
	Vec2 m_pos;
};