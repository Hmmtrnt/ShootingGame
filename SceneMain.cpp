#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneFail.h"
#include "ShotNormal.h"
#include "ShotBase.h"
#include "Pad.h"
#include <cassert>

namespace
{
	// �v���C���[�̕\���ʒu
	constexpr float kPlayerX = 100.0f;
	constexpr float kPlayerY = Game::kScreenHeight / 2;
	// �e�̕\���ʒu
	constexpr float kShotX = 0.0f;
	constexpr float kShotY = 0.0f;
	// �ȉ~�`�̂��ꂼ��̔��a
	constexpr int kRadiusX = 7;
	constexpr int kRadiusY = 4;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
	m_hFieldGraphic = -1;
	m_hEnemyGraphic = -1;
	m_enemyNum = 0;
	m_shotNum = 0;
	m_time = 0;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{

	/*�\���ʒu*/
	// �v���C���[
	m_posPlayer.x = 100.0f;
	m_posPlayer.y = Game::kScreenHeight / 2;
	// �e
	m_posShot.x = 0.0f;
	m_posShot.y = 0.0f;
	// �e�̕�
	m_sizeShot.x = 10.0f;
	m_sizeShot.y = 10.0f;
	// �G
	m_posEnemy.x = 540.0f;
	m_posEnemy.y = Game::kScreenWidth / 2;
	// �G�̕�
	m_sizeEnemy.x = 30.0f;
	m_sizeEnemy.y = 30.0f;
	// �v���C���[
	m_hPlayerGraphic = LoadGraph("data/player2.png");
	// �e
	m_hShotGraphic = DrawBox(m_posShot.x, m_posShot.y, m_posShot.x + m_sizeShot.x, m_posShot.y + m_sizeShot.y, GetColor(255, 255, 255), true);
	// �w�i
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
	// �G
	m_hEnemyGraphic = LoadGraph("data/enemy2.png");
	// �G�̐�
	m_enemyNum = 1;
	// �e�̐�
	m_shotNum = 3;
	// ����
	m_time = 50;

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);

	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}

void SceneMain::end()
{
	DeleteGraph(m_hFieldGraphic);
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphic);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}

SceneBase* SceneMain::update()
{
	m_enemy.update();
	m_player.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		// �e���˂������̏���
		auto& pShot = (*it);
		if (!pShot)
		{
			
			it++;
			continue;
		}
		pShot->update();
		// �G�̓����蔻��
		if (m_enemy.isCol(*pShot))
		{
			m_enemy.setDead(true);
			m_enemyNum--;
		}
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;
			// vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}

	// �V�[���ړ�(�\��ł͓G�ɒe�����������烊�U���g)
	if (m_enemyNum == 0)
	{
		return (new SceneResult);
	}
	else if (m_shotNum == 0)
	{
		m_time--;
		if (m_time == 0)
		{
			return (new SceneFail);
		}
	}
	return this;
}

void SceneMain::draw()
{
	DrawGraph(0, 0, m_hFieldGraphic, false);
	m_enemy.draw();
	m_player.draw();
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;
		pShot->draw();
	}

	DrawFormatString(0, 20, GetColor(0, 0, 0), "���%d", m_enemyNum);
	DrawString(0, 0, "���C�����", GetColor(0, 0, 0));
	DrawFormatString(0, 40, GetColor(0, 0, 0), "�e:%d", m_shotNum);
}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);
	m_shotNum--;

	return true;
}