/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emergence.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:27:37 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 14:46:06 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

static void	init_events(t_display *display, t_image *image)
{
	mlx_loop_hook(display->mlx_ptr, &loop_handler, image);
	mlx_hook(display->win_ptr, DestroyNotify, StructureNotifyMask,
		&red_cross_handler, image);
	mlx_hook(display->win_ptr, KeyRelease, KeyReleaseMask, &keys_handler, image);
	mlx_hook(display->win_ptr, ButtonPress, ButtonPressMask,
		&button_handler, image);
	mlx_hook(display->win_ptr, MotionNotify, PointerMotionMask,
		&pointer_handler, image);
}

int	main(int argc, char **argv)
{
	t_display	*display;
	t_image		*image;

	check_args(argc, argv);
	display = init_display("Screensaver", argv);
	image = init_image(display, ft_atoi(argv[3]));
	init_events(display, image);
	mlx_loop(display->mlx_ptr);
	free_n_destroy(image, display);
	ft_putstr_fd("Stopping...\n\033[0;32mThanks for using fract'ol!\033[0m\n", 1);
	return (0);
}
