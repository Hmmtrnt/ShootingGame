#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneFail.h"
#include "SceneTitle.h"

namespace
{
	// �G�̃W�����v��
	constexpr float kJumpEnemy = -15.0f;
	// �G�̏d��
	constexpr float kGravity = 1.0f;
}

SceneFail::SceneFail()
{
	m_fieldHandle = 0;	// �w�i
	m_enemyHandle = 0;	// �G
	m_fontHandle = 0;	// ����
	m_pos.x = 0;		// �\���ʒu
	m_pos.y = 0;
	m_vec.x = 0;		// �ړ����x
	m_vec.y = 0;
	m_size.x = 0;		// �T�C�Y
	m_size.y = 0;
	m_fieldY = 400;		// �n�ʂ̍���
}


void SceneFail::init()
{
	m_enemyHandle = LoadGraph("data/enemy2.png");		// �G
	m_fieldHandle = LoadGraph("data/field2.jpg");		// �w�i
	m_fontHandle = CreateFontToHandle(NULL, 40, 3);		// ����
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);	// �G�̃T�C�Y

	m_pos.x = 80;		// �G��X���W
	m_pos.y = m_fieldY;	// �G��Y���W
}
// �I��
void SceneFail::end()
{
	// �O���t�B�b�N�������̏���
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_fieldHandle);
}
// ���t���[���̏���
SceneBase* SceneFail::update()
{
	m_pos += m_vec;
	// �n�ʔ���
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}
	// �W�����v����
	if (isField)
	{
		// �W�����v
		m_vec.y = kJumpEnemy;
	}
	// �d��
	m_vec.y += kGravity;

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		// �^�C�g��
		return (new SceneTitle);
	}
	if (padState & PAD_INPUT_2)
	{
		// ���C��
		return (new SceneMain);
	}
	return this;
}

void SceneFail::draw()
{
	// �w�i
	DrawGraphF(0, 0, m_fieldHandle, true);
	// �e�L�X�g
	DrawFormatString(Game::kScreenWidth / 2 - 120, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "��u�I���͐����c�������I�v");
	DrawStringToHandle(Game::kScreenWidth / 2 - 160, Game::kScreenHeight / 2 - 100, "�f�`�l�d�n�u�d�q", GetColor(255, 0, 0), m_fontHandle);
	DrawGraphF(m_pos.x, m_pos.y, m_enemyHandle, true);
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "�P�{�^��:�@�^�C�g�����", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "�Q�{�^��:���X�^�[�g���", GetColor(0, 0, 0));
}