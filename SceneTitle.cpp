#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"

namespace
{
	// �t�F�[�h
	constexpr int kFadeBright = 0;		// ����
	constexpr int kFadeSpeed = 5;		// ���x
	// �`��P�x
	constexpr int kRedBright = 255;		// ��
	constexpr int kGreenBright = 255;	// ��
	constexpr int kBlueBright = 255;	// ��
}

SceneTitle::SceneTitle()
{
	m_hFieldGraphic = 0;	// �w�i�̃O���t�B�b�N�n���h��
	m_fadeBright = 0;		// �t�F�[�h����
	m_fadeSpeed = 0;		// �t�F�[�h���x
}

void SceneTitle::init()
{
	m_fadeBright = kFadeBright;	// �t�F�[�h����
	m_fadeSpeed = kFadeSpeed;	// �t�F�[�h���x
	// �w�i
	m_hFieldGraphic = LoadGraph("data/field2.jpg");
}

void SceneTitle::end()
{
	// �`��P�x
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
	// �O���t�B�b�N����������폜
	DeleteGraph(m_hFieldGraphic);
}

SceneBase* SceneTitle::update()
{
	// �t�F�[�h�A�E�g�̏���
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		m_fadeBright = 0;
		return(new SceneMain);
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)
	{
		// �t�F�[�h�A�E�g�J�n
		if (padState & PAD_INPUT_1)
		{
			m_fadeSpeed = -5;
		}
	}
	
	return this;
}

void SceneTitle::draw()
{
	// �`��P�x
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// �w�i
	DrawGraph(0, 0, m_hFieldGraphic, true);
	DrawString(Game::kScreenWidth / 2 - 50, Game::kScreenHeight / 2 - 80, "������āI", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 85, Game::kScreenHeight / 2, "�@�@�@�������\n�P�{�^���@�@:����\n���X�e�B�b�N:�㉺�ړ�", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 125, Game::kScreenHeight / 2 + 60, "�S�{�^���ł��ł��I���ł��܂�", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 75, Game::kScreenHeight / 2 + 130, "�P�{�^���ŃX�^�[�g", GetColor(0, 0, 0));
}