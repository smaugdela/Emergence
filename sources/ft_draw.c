/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:56:01 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 15:01:18 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

void	draw_pixel(t_image *image, size_t x, size_t y, int color)
{
	char	*pixel;
	int		i;

	if (x > image->display->win_w || x < 0
		|| y > image->display->win_h || y < 0)
	{
		ft_putstr_fd("\033[1;31mAccessing unmapped pixel.\033[0m\n", 2);
		return ;
	}
	pixel = image->addr + (y * image->size_line + x * (image->bpp / 8));
	i = image->bpp;
	while (i >= 8)
	{
		i -= 8;
		if (image->endian == 1)
			*pixel = (color >> i) & 255;
		else
			*pixel = (color >> (image->bpp - i - 8)) & 255;
		++pixel;
	}
}

int	clear_window(t_image *image, int color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < image->display->win_w)
	{
		j = 0;
		while (j < image->display->win_h)
		{
			if (get_pixel_color(i, j, image) > 0)
				draw_pixel(image, i, j, color);
			++j;
		}
		++i;
	}
	return (0);
}

void	clear_window_fade(t_image *image)
{
	int		r;
	int		g;
	int		b;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < image->display->win_w)
	{
		j = 0;
		while (j < image->display->win_h)
		{
			if (get_pixel_color(i, j, image) > 0)
			{
				r = get_pixel_color(i, j, image) >> 16;
				g = get_pixel_color(i, j, image) >> 8;
				b = get_pixel_color(i, j, image);
				draw_pixel(image, i, j,
					r * 0.9 * 0x010000 + g * 0.9 * 0x000100 + b * 0.9);
			}
			++j;
		}
		++i;
	}
}
