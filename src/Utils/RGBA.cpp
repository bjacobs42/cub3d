/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGBA.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:23:36 by bjacobs           #+#    #+#             */
/*   Updated: 2025/07/16 20:30:13 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/RGBA.hpp"

RGBA::RGBA(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
	: _r(r), _g(g), _b(b), _a(a)
{}

RGBA::RGBA(const uint32_t &color)
{
	*this = color;
}

RGBA::RGBA(const RGBA &source)
{
	*this = source;
}

RGBA::~RGBA(void)
{}

RGBA	&RGBA::operator=(const RGBA &rightSide)
{
	if (this != &rightSide)
	{
		_r = rightSide._r;
		_g = rightSide._g;
		_b = rightSide._b;
		_a = rightSide._a;
	}
	return (*this);
}

RGBA	&RGBA::operator=(const uint32_t &rightSide)
{
	_r = (rightSide >> 24) & 0xFF;
	_g = (rightSide >> 16) & 0xFF;
	_b = (rightSide >> 8) & 0xFF;
	_a = rightSide & 0xFF;
	return (*this);
}

void	RGBA::setRed(const uint8_t red)
{
	_r = red;
}

void	RGBA::setGreen(const uint8_t green)
{
	_g = green;
}

void	RGBA::setBlue(const uint8_t blue)
{
	_b = blue;
}

void	RGBA::setAlpha(const uint8_t alpha)
{
	_a = alpha;
}

uint8_t	RGBA::getRed(void) const
{
	return (_r);
}

uint8_t	RGBA::getGreen(void) const
{
	return (_g);
}

uint8_t	RGBA::getBlue(void) const
{
	return (_b);
}

uint8_t	RGBA::getAlpha(void) const
{
	return (_a);
}

uint32_t	RGBA::toInt32(void) const
{
	return ((_r << 24) | (_g << 16) | (_b << 8) | _a);
}

uint32_t	RGBA::lerp(const RGBA &rightSide, const float &t) const
{
	RGBA	result;

	result.setRed(_r * (1.0f - t) + rightSide._r * t);
	result.setGreen(_g * (1.0f - t) + rightSide._g * t);
	result.setBlue(_b * (1.0f - t) + rightSide._b * t);
	result.setAlpha(_a * (1.0f - t) + rightSide._a * t);
	return (result.toInt32());
}

uint32_t	RGBA::lerp(const RGBA &color1, const RGBA &color2, const float &t)
{
	RGBA	result;

	result.setRed(color1._r * (1.0f - t) + color2._r * t);
	result.setGreen(color1._g * (1.0f - t) + color2._g * t);
	result.setBlue(color1._b * (1.0f - t) + color2._b * t);
	result.setAlpha(color1._a * (1.0f - t) + color2._a * t);
	return (result.toInt32());
}

std::ostream&	operator<<(std::ostream& os, const RGBA& color)
{
	os << int(color.getRed()) << ","  << int(color.getGreen())
		<< "," << int(color.getBlue()) << "," << int(color.getAlpha());
	return (os);
}
