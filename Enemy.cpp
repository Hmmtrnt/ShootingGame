#include "DxLib.h"
#include "Enemy.h"
#include "game.h"
#include "SceneResult.h"
#include "ShotNormal.h"

Enemy::Enemy()
{
	m_speedY = 0;
	m_speedRand = 0;
	m_enemyHandle = 0;
	m_pMain = nullptr;
	m_isDead = false;
	vecY = 0;
	m_soundHandle = 0;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	// �X�s�[�h�̕ϐ�
	m_speedY = 25;
	// �G�̈ʒu
	m_pos.x = 500.0f;
	m_pos.y = Game::kScreenHeight / 2;
	// �G�̈ړ����x
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	// �X�s�[�h�̑����
	vecY = m_speedY;
	// ���̃n���h��
	m_soundHandle = LoadSoundMem("sound/enemySound2.mp3");
}
// �O���t�B�b�N�f�[�^�ݒ�
void Enemy::setHandle(int handle)
{
	m_enemyHandle = handle;
	GetGraphSizeF(m_enemyHandle, &m_size.x, &m_size.y);
}
// ���t���[���̏���
void Enemy::update()
{
	// �G�̃����_���ȑ��x
	m_speedRand = GetRand(25) + 5;

	// ���S
	if (m_isDead)	return;
	m_pos.y += vecY;
	// ��ʂ̈�ԏ�ɍs�������̏���
	if (m_pos.y < -20)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
		m_speedY = m_speedRand;
		vecY = m_speedY;
	}
	// ��ʂ̈�ԉ��ɍs�������̏���
	if (m_pos.y > Game::kScreenHeight - getColSize().y + 10)
	{
		PlaySoundMem(m_soundHandle, DX_PLAYTYPE_BACK);
		m_speedY = m_speedRand;
		vecY = -m_speedY;
	}
}
// �G�̕`��
void Enemy::draw()
{
	// ���S
	if (m_isDead)	return;
	DrawTurnGraph(m_pos.x, m_pos.y, m_enemyHandle, true);
}
// �G�ƒe�̓����蔻��
bool Enemy::isCol(ShotBase& shotBase)
{
	// �e�̓����蔻��
	float shotLeft = shotBase.getPos().x - shotBase.getSize().x;
	float shotRight = shotBase.getPos().x + shotBase.getSize().x;
	float shotTop = shotBase.getPos().y - shotBase.getSize().y;
	float shotBottom = shotBase.getPos().y + shotBase.getSize().y;
	// �G�̓����蔻��
	float enemyLeft = getPos().x + 15;
	float enemyRight = getPos().x + getColSize().x;
	float enemyTop = getPos().y + 20;
	float enemyBottom = getPos().y + getColSize().y - 10;
	// �������Ă��Ȃ�����
	if (shotLeft > enemyRight)	return false;
	if (shotRight < enemyLeft)	return false;
	if (shotTop > enemyBottom)	return false;
	if (shotBottom < enemyTop)	return false;
	// ������������
	return true;
}