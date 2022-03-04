/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boids_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:02:52 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 17:37:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

static void	compute_accel(size_t index, t_boid *boids, size_t nb_boids)
{
	size_t	i;
	double	dist;

	i = 0;
	while (i < nb_boids)
	{
		if (i != index)
		{
			dist = sqrt(pow(boids[index].x - boids[i].x, 2) +
					pow(boids[index].y - boids[i].y, 2));
			if (dist < VIEW_RANGE)
			{
				boids[index].x_acc += boids[i].x_vel * FOLLOW_RATE / dist;
				boids[index].y_acc += boids[i].y_vel * FOLLOW_RATE / dist;
			}
		}
		i++;
	}
	if (boids[index].x_acc >= MAX_ACCEL)
	{
		boids[index].x_acc = MAX_ACCEL - 0.1 * MAX_ACCEL;
		
	}
	else if (boids[index].x_acc <= -MAX_ACCEL)
	{
		boids[index].x_acc = -MAX_ACCEL + 0.1 * MAX_ACCEL;
	}
	if (boids[index].y_acc >= MAX_ACCEL)
	{
		boids[index].y_acc = MAX_ACCEL - 0.1 * MAX_ACCEL;
	}
	else if (boids[index].y_acc <= -MAX_ACCEL)
	{
		boids[index].y_acc = -MAX_ACCEL + 0.1 * MAX_ACCEL;
	}
}

void boids_move(t_image *image)
{
	int		i;

	i = 0;
	while (i < image->nb_boids)
	{
		compute_accel(i, image->boids, image->nb_boids);
		image->boids[i].x_vel += image->boids[i].x_acc;
		image->boids[i].y_vel += image->boids[i].y_acc;
		if (image->boids[i].x_vel > MAX_SPEED)
			image->boids[i].x_vel = MAX_SPEED;
		else if (image->boids[i].x_vel < -MAX_SPEED)
			image->boids[i].x_vel = -MAX_SPEED;
		if (image->boids[i].y_vel > MAX_SPEED)
			image->boids[i].y_vel = MAX_SPEED;
		else if (image->boids[i].y_vel < -MAX_SPEED)
			image->boids[i].y_vel = -MAX_SPEED;
		image->boids[i].x += image->boids[i].x_vel;
		image->boids[i].y += image->boids[i].y_vel;
		if (image->boids[i].x < 0)
			image->boids[i].x += image->display->win_w;
		else if (image->boids[i].x > image->display->win_w)
			image->boids[i].x -= image->display->win_w;
		if (image->boids[i].y < 0)
			image->boids[i].y += image->display->win_h;
		else if (image->boids[i].y > image->display->win_h)
			image->boids[i].y -= image->display->win_h;
		++i;
	}
}
