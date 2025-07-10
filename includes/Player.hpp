#pragma once

#include "Vec2.hpp"

class Player
{
	private:
		Vec2<double>	_speed;
		Vec2<double>	_position;
		float			_look_angle;

	public:
		Player(void) : _look_angle(0) {};
		Player(const Vec2<double>& speed, const Vec2<double>& pos, const float& angle)
			: _speed(speed), _position(pos), _look_angle(angle) {}
		Player(const Player& source) { *this = source; }
		~Player(void);

		Player& operator=(const Player& source)
		{
			if (this != &source)
			{
				_speed = source._speed;
				_position = source._position;
				_look_angle =  source._look_angle;
			}
			return (*this);
		}


};
