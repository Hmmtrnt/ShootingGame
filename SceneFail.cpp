#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneFail.h"
#include "SceneTitle.h"
#include "Pad.h"

namespace
{
	// �G�̈ʒu
	constexpr int kPosEnemy = 80;
	// �n�ʂ̍���
	constexpr int kFieldY = 400;
	// �t�H���g
	constexpr int kSizeFont = 40;	// �T�C�Y
	constexpr int kThickFont = 3;	// ����
	// �G�̃W�����v��
	constexpr float kJumpEnemy = -15.0f;
	// �G�̏d��
	constexpr float kGravity = 1.0f;
	// �t�F�[�h
	constexpr int kFadeBright = 0;		// ����
	constexpr int kFadeSpeed = 5;		// ���x
	// �`��P�x
	constexpr int kRedBright = 255;		// ��
	constexpr int kGreenBright = 255;	// ��
	constexpr int kBlueBright = 255;	// ��
}

SceneFail::SceneFail()
{
	m_fieldHandle = 0;	// �w�i
	m_enemyHandle = 0;	// �G
	m_fontHandle = 0;	// ����
	m_fadeBright = 0;	// �t�F�[�h����
	m_fadeSpeed = 0;	// �t�F�[�h���x
	m_input1 = 0;		// ���͏��P
	m_input2 = 0;		// ���͏��Q
	m_pos.x = 0;		// �\���ʒu
	m_pos.y = 0;
	m_vec.x = 0;		// �ړ����x
	m_vec.y = 0;
	m_size.x = 0;		// �T�C�Y
	m_size.y = 0;
	m_fieldY = kFieldY;		// �n�ʂ̍���
}


void SceneFail::init()
{
	m_enemyHandle = LoadGraph("data/enemy2.png");		// �G
	m_fieldHandle = LoadGraph("data/field2.jpg");		// �w�i
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);		// ����
	m_fadeBright = kFadeBright;	// �t�F�[�h����
	m_fadeSpeed = kFadeSpeed;	// �t�F�[�h���x
	m_input1 = 0;			// ���͏��P
	m_input2 = 0;			// ���͏��Q
	
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);	// �G�̃T�C�Y

	m_pos.x = kPosEnemy;		// �G��X���W
	m_pos.y = m_fieldY;	// �G��Y���W
}
// �I��
void SceneFail::end()
{
	// �O���t�B�b�N�������̏���
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_fieldHandle);
	DeleteFontToHandle(m_fontHandle);
	// �`��P�x
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
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
	// �t�F�[�h�A�E�g�̏���
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_input1 > 0)
	{
		m_fadeBright = 0;
		return(new SceneTitle);
	}
	if (m_fadeBright <= 0 && m_fadeSpeed < 0 && m_input2 > 0)
	{
		m_fadeBright = 0;
		return(new SceneMain);
	}

	if (m_fadeSpeed == 0)
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
		{
			m_fadeSpeed = -kFadeSpeed;
		}
	}

	if (m_fadeBright == 255)
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			m_input1++;
		}
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			m_input2++;
		}
	}
	

	return this;
}

void SceneFail::draw()
{
	// �`��P�x
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// �w�i
	DrawGraphF(0, 0, m_fieldHandle, true);
	// �e�L�X�g
	DrawFormatString(Game::kScreenWidth / 2 - 120, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "��u�I���͐����c�������I�v");
	DrawStringToHandle(Game::kScreenWidth / 2 - 160, Game::kScreenHeight / 2 - 100, "�f�`�l�d�n�u�d�q", GetColor(255, 0, 0), m_fontHandle);
	DrawGraphF(m_pos.x, m_pos.y, m_enemyHandle, true);
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "�P�{�^��:�@�^�C�g��", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "�Q�{�^��:���X�^�[�g", GetColor(0, 0, 0));
}