#include "Game/Player/Player.hpp"

#define PI 3.14159265359f
#define HALF_PI 1.57079632679f
#define TWO_PI 6.28318530718f
#define THIRD_PI 4.71238898038f

float	Player::_dirCharToAngle(char c)
{
	switch (c)
	{
		case 'N': return (HALF_PI);
		case 'W': return (PI);
		case 'S': return (THIRD_PI);
		default: return (0.0f);
	}
}

Player::Player(const Vec2<double>& pos, char dirChar)
	: _camera(pos, _dirCharToAngle(dirChar)) {}

Player::Player(const Player& source)
	: _camera(source._camera) {}
