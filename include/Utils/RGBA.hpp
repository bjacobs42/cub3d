/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGBA.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:14:49 by bjacobs           #+#    #+#             */
/*   Updated: 2025/07/11 21:19:30 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define BLACK		0x000000FF
#define WHITE		0xFFFFFFFF
#define INVISIBLE	0xFFFFFF00

#include <ostream>
#include <cstdint>

class RGBA
{
	private:
		uint8_t	_r;
		uint8_t	_g;
		uint8_t	_b;
		uint8_t	_a;

	public:
		RGBA(const uint8_t r = 0, const uint8_t g = 0, const uint8_t b = 0, const uint8_t a = 0xFF);
		RGBA(const uint32_t &color);
		RGBA(const RGBA &source);
		~RGBA(void);

		RGBA			&operator=(const RGBA &rightSide);
		RGBA			&operator=(const uint32_t &rightSide);

		void			setRed(const uint8_t red);
		void			setGreen(const uint8_t green);
		void			setBlue(const uint8_t blue);
		void			setAlpha(const uint8_t alpha);

		uint8_t			getRed(void) const;
		uint8_t			getGreen(void) const;
		uint8_t			getBlue(void) const;
		uint8_t			getAlpha(void) const;

		uint32_t		toInt32(void) const;
		uint32_t		lerp(const RGBA &rightSide, const float &t) const;

		static uint32_t	lerp(const RGBA &color1, const RGBA &color2, const float &t);
};

std::ostream&	operator<<(std::ostream& os, const RGBA& color);
