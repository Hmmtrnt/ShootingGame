#include "DxLib.h"
#include "ShotBase.h"

ShotBase::ShotBase()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_size.x = 10.0f;
	m_size.y = 5.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}

ShotBase::~ShotBase()
{

}

void ShotBase::start(Vec2 pos)
{
	m_isExist = true;

	pos.x += 35.0f;
	pos.y += 25.0f;

	m_pos = pos;
}

void ShotBase::update()
{
	if (!m_isExist) return;
}

void ShotBase::draw()
{
	if (!m_isExist) return;
	
	DrawOval(m_pos.x, m_pos.y, m_size.x, m_size.y, GetColor(0, 0, 0), true);
}