#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "SceneFail.h"
#include "ShotNormal.h"
#include "ShotBase.h"
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
	m_hPlayerGraphic = 0;		// �v���C���[�̃O���t�B�b�N�n���h��
	m_hShotGraphic = 0;		// �V���b�g�̃O���t�B�b�N�n���h��
	m_hFieldGraphic = 0;		// �w�i�̃O���t�B�b�N�n���h��
	m_hEnemyGraphic = 0;		// �G�̃O���t�B�b�N�n���h��
	m_fontHandle = 0;			// �����̃n���h��
	m_enemyNum = 0;				// �G�̐�
	m_shotNum = 0;				// �e�̐�
	m_time = 0;					// �Ō�̈ꔭ�������I����Ă���Q�[���I�[�o�[�܂ł̎���
}
// ������
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
	// ����
	m_fontHandle = CreateFontToHandle(NULL, 50, 4);
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
// �I��
void SceneMain::end()
{
	// �O���t�B�b�N�������폜
	DeleteGraph(m_hFieldGraphic);
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphic);
	// �m�F����
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}
// ���t���[���̏���
SceneBase* SceneMain::update()
{
	m_enemy.update();
	m_player.update();
	// �x�N�^�[����
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
		// �e�����ׂČ����I������玞�Ԃ�����Q�[���I�[�o�[��ʂ�
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
	// �w�i
	DrawGraph(0, 0, m_hFieldGraphic, false);
	m_enemy.draw();		// �G
	m_player.draw();	// ���@
	// �e
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;
		pShot->draw();
	}
	// �e���\��
	DrawFormatStringFToHandle(0, 0, GetColor(0, 0, 0), m_fontHandle, "�e:%d", m_shotNum);
}
// �e�̐���
bool SceneMain::createShotNormal(Vec2 pos)
{
	// �e�̐����Ə��������ꂼ��m�F����
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);
	m_shotNum--;	// �e������

	return true;
}