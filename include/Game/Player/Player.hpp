#pragma once

#include "Camera.hpp"
#include "Utils/Vectors.hpp"

class Player
{
	private:
		Camera	_camera;

		static float _dirCharToAngle(char c);

	public:
		Player(const Vec2<double>& pos = {0, 0}, char dirChar = 'N');
		Player(const Player& source);
		~Player(void) {};
};
