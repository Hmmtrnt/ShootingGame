#pragma once

#include <vector>
#include "Enemy.h"
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
	// �G�l�~�[
	Enemy m_enemy;
	// �V���b�g
	std::vector<ShotBase*>m_pShotVt;
	/*�\���ʒu*/
	// �v���C���[
	Vec2 m_posPlayer;
	// �e
	Vec2 m_posShot;
	// �e�̕�
	Vec2 m_sizeShot;
	// �G
	Vec2 m_posEnemy;
	// �G�̕�
	Vec2 m_sizeEnemy;
};