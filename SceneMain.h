#pragma once

#include <vector>
#include "Enemy.h"
#include "player.h"
#include "SceneBase.h"
#include "ShotBase.h"
#include "ShotNormal.h"

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
	// �V���b�g�̃O���t�B�b�N�n���h��
	int m_hShotGraphic;
	// �w�i�̃O���t�B�b�N�n���h��
	int m_hFieldGraphic;
	// �G�̃O���t�B�b�N�n���h��
	int m_hEnemyGraphic;
	// �G�̐�
	int enemyNum;
	// �e�̐�
	int shotNum;
	// ����
	int time;

	// �v���C���[
	Player m_player;
	// �G�l�~�[
	Enemy m_enemy;
	// �V���b�g�x�[�X
	ShotBase m_shotBase;
	// �V���b�g�m�[�}��
	ShotNormal m_shotNormal;
	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
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