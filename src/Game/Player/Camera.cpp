#include "Game/Player/Camera.hpp"

Camera::Camera(const Vec2<double>& pos, float angle)
	: _position(pos), _angle(angle) {}

Camera::Camera(const Camera& source)
	: _position(source._position), _angle(source._angle) {}

Camera&	Camera::operator=(const Camera& source)
{
	if (this != &source)
	{
		this->_angle = source._angle;
		this->_position = source._position;
	}
	return (*this);
}
