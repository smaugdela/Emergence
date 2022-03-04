/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:45:38 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 15:05:00 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

int	loop_handler(t_image *image)
{
	int		i;

	i = 0;
	clear_window_fade(image);
	while (i < image->nb_boids)
	{
		draw_pixel(image, (size_t)image->boids[i].x, (size_t)image->boids[i].y,
			image->boids[i].color);
		/*
		printf("boid nb %d, x = %f y = %f velx = %f vely = %f xacc = %f yacc = %f color = %d maxspeed = %d maxaccel = %d\n", i,
			image->boids[i].x, image->boids[i].y,
			image->boids[i].x_vel, image->boids[i].y_vel,
			image->boids[i].x_acc, image->boids[i].y_acc,
			image->boids[i].color, image->boids[i].max_speed,
			image->boids[i].max_accel);
		*/
		i++;
	}
	mlx_put_image_to_window(image->display->mlx_ptr,
		image->display->win_ptr, image->image_ptr, 0, 0);
	boids_move(image);
	return (0);
}

int	keys_handler(int key_sym, t_image *image)
{
	if (key_sym == XK_Escape)
		red_cross_handler(image);
	return (0);
}

int	pointer_handler(int x, int y, t_image *image)
{
	(void)x;
	(void)y;
	(void)image;
	return (0);
}

int	button_handler(int button, int x, int y, t_image *image)
{
	(void)button;
	(void)x;
	(void)y;
	(void)image;
	return (0);
}
/*
Button value:
	clic gauche = 1
	clic droit = 3
	clic molette = 2
	molette /\ = 4
	molette \/ = 5
*/
