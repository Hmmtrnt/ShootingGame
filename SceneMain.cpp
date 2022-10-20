#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneFail.h"
#include "ShotNormal.h"
#include "ShotBase.h"
#include <cassert>

namespace
{
	// �v���C���[�̕\���ʒu
	constexpr float kPosPlayerX = 100.0f;
	constexpr float kPosPlayerY = Game::kScreenHeight / 2;
	// �e�̕\���ʒu
	constexpr float kPosShotX = 0.0f;
	constexpr float kPosShotY = 0.0f;
	// �e�̕�
	constexpr float kSizeShotX = 10.0f;
	constexpr float kSizeShotY = 10.0f;
	// �G�̈ʒu
	constexpr float kPosEnemyX = 540.0f;
	constexpr float kPosEnemyY = Game::kScreenWidth / 2;
	// �G�̕�
	constexpr float kSizeEnemyX = 30.0f;
	constexpr float kSizeEnemyY = 30.0f;
	// �t�H���g
	constexpr int kSizeFont = 50;	// �T�C�Y
	constexpr int kThickFont = 4;	// ����
	// �G�̐�
	constexpr int kEnemyNum = 1;
	// �e�̐�
	constexpr int kShotNum = 3;
	// ����
	constexpr int kTime = 40;
	// �t�F�[�h
	constexpr int kFadeBright = 0;		// ����
	constexpr int kFadeSpeed = 5;		// ���x
	// �`��P�x
	constexpr int kRedBright = 255;		// ��
	constexpr int kGreenBright = 255;	// ��
	constexpr int kBlueBright = 255;	// ��
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = 0;		// �v���C���[�̃O���t�B�b�N�n���h��
	m_hShotGraphic = 0;			// �V���b�g�̃O���t�B�b�N�n���h��
	m_hFieldGraphic = 0;		// �w�i�̃O���t�B�b�N�n���h��
	m_hEnemyGraphic = 0;		// �G�̃O���t�B�b�N�n���h��
	m_fontHandle = 0;			// �����̃n���h��
	m_enemyNum = 0;				// �G�̐�
	m_shotNum = 0;				// �e�̐�
	m_time = 0;					// �Ō�̈ꔭ�������I����Ă���Q�[���I�[�o�[�܂ł̎���
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
// ������
void SceneMain::init()
{

	/*�\���ʒu*/
	// �v���C���[
	m_posPlayer.x = kPosPlayerX;
	m_posPlayer.y = kPosPlayerY;
	// �e
	m_posShot.x = kPosShotX;
	m_posShot.y = kPosShotY;
	// �e�̕�
	m_sizeShot.x = kSizeShotX;
	m_sizeShot.y = kSizeShotY;
	// �G
	m_posEnemy.x = kPosEnemyX;
	m_posEnemy.y = kPosEnemyY;
	// �G�̕�
	m_sizeEnemy.x = kSizeEnemyX;
	m_sizeEnemy.y = kSizeEnemyY;
	// �v���C���[
	m_hPlayerGraphic = LoadGraph("data/player2.png");
	// �e
	m_hShotGraphic = DrawBox((int)m_posShot.x, (int)m_posShot.y, (int)m_posShot.x + (int)m_sizeShot.x, (int)m_posShot.y + (int)m_sizeShot.y, GetColor(255, 255, 255), true);
	// �w�i
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
	// �G
	m_hEnemyGraphic = LoadGraph("data/enemy2.png");
	// ����
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);
	// �G�̐�
	m_enemyNum = kEnemyNum;
	// �e�̐�
	m_shotNum = kShotNum;
	// ����
	m_time = kTime;
	// �t�F�[�h
	m_fadeBright = kFadeBright;	// ����
	m_fadeSpeed = kFadeSpeed;	// ���x

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
	DeleteFontToHandle(m_fontHandle);
	// �`��P�x
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
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

	// �t�F�[�h�A�E�g�̏���
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_enemyNum == 0)
	{
		m_fadeBright = 0;
		return(new SceneResult);
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_time == 0)
	{
		m_fadeBright = 0;
		return(new SceneFail);
	}

	if (m_fadeSpeed == 0)
	{
		// �t�F�[�h�A�E�g�J�n
		if (m_enemyNum == 0)
		{
			m_fadeSpeed = -5;
		}
		if (m_shotNum == 0)
		{
			m_time--;
			if (m_time == 0)
			{
				m_fadeSpeed = -5;
			}
		}
	}

	return this;
}

void SceneMain::draw()
{
	// �`��P�x
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
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
	// ���Ԋm�F
	DrawFormatString(0, 50, GetColor(0, 0, 0), "����:%d", m_time);
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