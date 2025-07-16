/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 23:36:03 by bjacobs           #+#    #+#             */
/*   Updated: 2025/07/16 21:36:38 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "MLX42.h"
#include <cstdint>

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 400

class Window
{
	private:
		const uint32_t	_width;
		const uint32_t	_height;
		mlx_t			*_mlx;
		mlx_image_t		*_img;

		void	_init(void);

	public:
		Window(void);
		Window(const int &width, const int &height);
		~Window(void);

		void		setImgColor(const uint32_t &color);

		mlx_t		*getMlx(void) const;
		mlx_image_t	*getImg(void) const;

		void		addHook(void (*hook)(void *param));
		void		loopHook(void);
};
