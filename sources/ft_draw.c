/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:56:01 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/03 15:19:48 by smagdela         ###   ########.fr       */
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