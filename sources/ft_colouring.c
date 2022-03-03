/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colouring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:49:19 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/03 15:21:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

int	get_pixel_color(size_t x, size_t y, t_image *image)
{
	char	*pixel;

	if (x > image->display->win_w || x < 0
		|| y > image->display->win_h || y < 0)
		return (42);
	pixel = image->addr + (y * image->size_line + x * (image->bpp / 8));
	return (*(int *)pixel);
}

int	color_bnw(int n, int max_iter)
{
	(void)n;
	(void)max_iter;
	return (0xffffff);
}

int	color_r(int n, int max_iter)
{
	int	r;

	r = -255 * ((double)n / (double)max_iter) + 255;
	return (0x010000 * r);
}

int	color_g(int n, int max_iter)
{
	int	g;

	g = -255 * ((double)n / (double)max_iter) + 255;
	return (0x000100 * g);
}

int	color_b(int n, int max_iter)
{
	int	b;

	b = -255 * ((double)n / (double)max_iter) + 255;
	return (b);
}
