/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boids_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:02:52 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/03 15:17:54 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

void boids_move(t_image *image)
{
	int		i;

	i = 0;
	while (i < image->nb_boids)
	{
		image->boids[i].x_vel += image->boids[i].x_acc;
		image->boids[i].y_vel += image->boids[i].y_acc;
		image->boids[i].x += image->boids[i].x_vel;
		image->boids[i].y += image->boids[i].y_vel;
		if (image->boids[i].x < 0)
			image->boids[i].x += image->display->win_w;
		if (image->boids[i].x > image->display->win_w)
			image->boids[i].x -= image->display->win_w;
		if (image->boids[i].y < 0)
			image->boids[i].y += image->display->win_h;
		if (image->boids[i].y > image->display->win_h)
			image->boids[i].y -= image->display->win_h;
		i++;
	}
}
