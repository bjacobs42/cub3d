#pragma once

#include "Utils/Vectors.hpp"
class Camera
{
	private:
		Vec2<double>	_position;
		float			_angle;

	public:
		Camera(const Vec2<double>& pos = {0, 0}, float angle = 0);
		Camera(const Camera& source);
		~Camera(void) {};

		Camera& operator=(const Camera& source);
};
