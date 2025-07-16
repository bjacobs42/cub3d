/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:51:04 by bjacobs           #+#    #+#             */
/*   Updated: 2025/07/16 21:36:29 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/Window.hpp"
#include <iostream>

void	Window::_init(void)
{
	_mlx = mlx_init(_width, _height, "♥", true);
	if (!_mlx)
		throw;
	_img = mlx_new_image(_mlx, _width, _height);
	if (!_img)
		throw;
	setImgColor(0);
}

Window::Window(void) : _width(DEFAULT_WIDTH), _height(DEFAULT_HEIGHT)
{
	_init();
}

Window::Window(const int &width, const int &height) : _width(width), _height(height)
{
	_init();
}

Window::~Window(void)
{
	if (_mlx)
		mlx_terminate(_mlx);
}

void	Window::setImgColor(const uint32_t &color)
{
	uint32_t	x, y;

	for (x = 0; x < _img->width; ++x)
	{
		for (y  = 0; y < _img->height; ++y)
			mlx_put_pixel(_img, x, y, color);
	}
}

mlx_t	*Window::getMlx(void) const
{
	return (_mlx);
}

mlx_image_t	*Window::getImg(void) const
{
	return (_img);
}

void	Window::addHook(void (*hook)(void *param))
{
	if (!mlx_loop_hook(_mlx, hook, (void *)this))
		throw;
}

void	Window::loopHook(void)
{
	if (mlx_image_to_window(_mlx, _img, 0, 0) == -1)
		throw;
	mlx_loop(_mlx);
}
