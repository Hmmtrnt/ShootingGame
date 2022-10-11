#include "DxLib.h"
#include "ShotBase.h"

namespace
{
	constexpr float kShotSpeed = 10.0f;
	// ‘È‰~Œ`‚Ì‚»‚ê‚¼‚ê‚Ì”¼Œa
	constexpr int kRadiusX = 5;
	constexpr int kRadiusY = 3;
}

ShotBase::ShotBase()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

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
	m_pos = pos;
}

void ShotBase::update()
{
	if (!m_isExist) return;
}

void ShotBase::draw()
{
	if (!m_isExist) return;
	DrawOval(m_pos.x, m_pos.y, kRadiusX, kRadiusY, GetColor(255, 255, 255), true);
}