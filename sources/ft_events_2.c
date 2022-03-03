/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:57:13 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/03 14:05:33 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

int	red_cross_handler(t_image *image)
{
	free_n_destroy(image, image->display);
	ft_putstr_fd("Closing...\n\033[0;32mThanks for using fract'ol!\033[0m\n", 1);
	exit(EXIT_SUCCESS);
	return (0);
}
