#include "DxLib.h"
#include "Vec2.h"
#include "player.h"

namespace
{
	// Y�����̑��x
	constexpr float kSpeedMaxY = 8.0f;

}

Player::Player()
{

}

Player::~Player()
{

}

void Player::init()
{

}

void Player::update()
{

}

void Player::draw()
{
	// �����@
	DrawCircle(100, 240, 50, GetColor(255, 255, 255));
}