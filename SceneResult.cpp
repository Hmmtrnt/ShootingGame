#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneTitle.h"

namespace
{
	// �t�H���g
	constexpr int kSizeFont = 40;	// �T�C�Y
	constexpr int kThickFont = 3;	// ����
	// �t�F�[�h
	constexpr int kFadeBright = 0;		// ����
	constexpr int kFadeSpeed = 5;		// ���x
	// �`��P�x
	constexpr int kRedBright = 255;		// ��
	constexpr int kGreenBright = 255;	// ��
	constexpr int kBlueBright = 255;	// ��
}

SceneResult::SceneResult()
{
	m_hFieldHandle = 0;		// �w�i
	m_fontHandle = 0;		// �t�H���g
	m_fadeBright = 0;		// �t�F�[�h����
	m_fadeSpeed = 0;		// �t�F�[�h���x
	m_input1 = 0;			// ���͏��P
	m_input2 = 0;			// ���͏��Q
}
// ������
void SceneResult::init()
{
	// �w�i�f�[�^
	m_hFieldHandle = LoadGraph("data/field2.jpg");
	// �t�H���g�f�[�^
	m_fontHandle = CreateFontToHandle(NULL, kSizeFont, kThickFont);
	m_fadeBright = kFadeBright;	// �t�F�[�h����
	m_fadeSpeed = kFadeSpeed;	// �t�F�[�h���x
	m_input1 = 0;			// ���͏��P
	m_input2 = 0;			// ���͏��Q
}
// �I��
void SceneResult::end()
{
	// �`��P�x
	SetDrawBright(kRedBright, kGreenBright, kBlueBright);
	// �O���t�B�b�N����������
	DeleteGraph(m_hFieldHandle);
	DeleteFontToHandle(m_fontHandle);
}
// ���t���[���̏���
SceneBase* SceneResult::update()
{
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
		if (padState & PAD_INPUT_1 || padState & PAD_INPUT_2)
		{
			m_fadeSpeed = -kFadeSpeed;
		}
	}

	if (padState & PAD_INPUT_1)
	{
		m_input1++;
	}
	if (padState & PAD_INPUT_2)
	{
		m_input2++;
	}

	//int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (padState & PAD_INPUT_1)
	//{
	//	return (new SceneTitle);
	//}
	//if (padState & PAD_INPUT_2)
	//{
	//	return (new SceneMain);
	//}
	//
	return this;
}
// �`��
void SceneResult::draw()
{
	// �`��P�x
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// �w�i
	DrawGraph(0, 0, m_hFieldHandle, true);
	// ����
	DrawStringToHandle(Game::kScreenWidth / 2 - 170, Game::kScreenHeight / 2 - 100, "�f�`�l�d�b�k�d�`�q", GetColor(0, 0, 0), m_fontHandle);
	DrawFormatString(Game::kScreenWidth / 2 - 140, Game::kScreenHeight / 2 + 120, GetColor(0, 0, 0), "��l���u����ň��S���ĉ߂����������v");
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2, "�P�{�^��:�@�^�C�g��", GetColor(0, 0, 0));
	DrawString(Game::kScreenWidth / 2 - 90, Game::kScreenHeight / 2 + 20, "�Q�{�^��:���X�^�[�g", GetColor(0, 0, 0));
}