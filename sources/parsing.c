/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:20:38 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/03 14:26:34 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emergence.h"

static void	usage(void)
{
	ft_putstr_fd("Usage: ./emergence <window width> <window height>", 1);
	ft_putstr_fd(" <number of boids> ", 1);
	ft_putstr_fd("\n\nExample:    ./emergence 1920 1080 100\n\n", 1);
	exit (FALSE);
}

void	check_args(int argc, char **argv)
{
	if (argc != 4)
		usage();
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1)
		usage();
	if (ft_atoi(argv[1]) > 4000 || ft_atoi(argv[2]) > 4000)
		usage();
	if (ft_atoi(argv[3]) >= ft_atoi(argv[1]) * ft_atoi(argv[2]))
		usage();
}
