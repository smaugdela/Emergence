/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:30:00 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 17:11:37 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

void	ft_error(const char *ft_name)
{
	ft_putstr_fd("Error: ", 2);
	perror(ft_name);
	exit(EXIT_FAILURE);
}

void	free_n_destroy(t_image *image, t_display *display)
{
	if (image && image->image_ptr)
		mlx_destroy_image(image->display->mlx_ptr, image->image_ptr);
	if (image)
	{
		if (image->boids)
			free(image->boids);
		free(image);
		image = NULL;
	}
	if (display && display->win_ptr)
	{
		mlx_destroy_window(display->mlx_ptr, display->win_ptr);
		display->win_ptr = NULL;
	}
	if (display && display->mlx_ptr)
	{
		mlx_destroy_display(display->mlx_ptr);
		free(display->mlx_ptr);
		display->mlx_ptr = NULL;
	}
	if (display)
	{
		free(display);
		display = NULL;
	}
}

static void	init_boids(int nb_boids, t_image *image)
{
	t_boid	*boids_tmp;
	int		i;

	boids_tmp = malloc(sizeof(t_boid) * nb_boids);
	if (!boids_tmp)
	{
		free_n_destroy(image, image->display);
		ft_error("malloc");
	}
	i = 0;
	while (i < nb_boids)
	{
		boids_tmp[i].x = (i * image->display->win_w / 10)
			% image->display->win_w;
		boids_tmp[i].y = ((i / 10 + 1) * (image->display->win_h / 10))
			% image->display->win_h;
		boids_tmp[i].x_vel = random() * (double)MAX_SPEED / (double)RAND_MAX *
			(random() % 2 == 0 ? 1 : -1);
		boids_tmp[i].y_vel = random() * (double)MAX_SPEED / (double)RAND_MAX *
			(random() % 2 == 0 ? 1 : -1);
		boids_tmp[i].x_acc = 0;
		boids_tmp[i].y_acc = 0;
		boids_tmp[i].color = 0xFFFFFF;
		++i;
	}
	image->boids = boids_tmp;
}

t_image	*init_image(t_display *display, int nb_boids)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (image == NULL)
	{
		free(display);
		ft_error("malloc");
	}
	if (image == NULL || display == NULL)
	{
		free_n_destroy(image, display);
		ft_error("init_image");
	}
	image->display = display;
	image->image_ptr = mlx_new_image(display->mlx_ptr,
			display->win_w, display->win_h);
	image->addr = mlx_get_data_addr(image->image_ptr,
			&image->bpp, &image->size_line, &image->endian);
	if (image == NULL || image->image_ptr == NULL || image->addr == NULL)
	{
		free_n_destroy(image, display);
		ft_error("mlx_new_image");
	}
	image->nb_boids = nb_boids;
	init_boids(nb_boids, image);
	return (image);
}

t_display	*init_display(char *win_name, char **argv)
{
	t_display	*display;

	display = malloc(sizeof(t_display));
	if (display == NULL)
		ft_error("malloc");
	display->mlx_ptr = mlx_init();
	if (display->mlx_ptr == NULL)
	{
		free(display);
		ft_error("mlx_init");
	}
	display->win_w = ft_atoi(argv[1]);
	display->win_h = ft_atoi(argv[2]);
	display->win_ptr = mlx_new_window(display->mlx_ptr,
			display->win_w, display->win_h, win_name);
	if (display->win_ptr == NULL)
	{
		free_n_destroy(NULL, display);
		ft_error("mlx_new_window");
	}
	return (display);
}
