/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emergence.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:24:29 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/04 17:33:18 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMERGENCE_H
# define EMERGENCE_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

# define TRUE	1
# define FALSE	0

typedef uint8_t	t_bool;

# define MAX_SPEED	5 // In pixels per frame
# define MAX_ACCEL	0.01 // In pixels per frame squared
# define VIEW_RANGE	500 // In pixels
# define FOLLOW_RATE	1 //

/* Boids structure */
typedef struct s_boid{
	double	x;
	double	y;
	double	x_vel;
	double	y_vel;
	double	x_acc;
	double	y_acc;
	int		color;
}	t_boid;

/* Data structures for mlx */
typedef struct s_display {
	void	*mlx_ptr;
	void	*win_ptr;
	size_t	win_w;
	size_t	win_h;
}	t_display;

typedef struct s_image {
	t_display	*display;
	void		*image_ptr;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_boid		*boids;
	int			nb_boids;
}	t_image;

/* Geometry structures */
typedef struct s_circle {
	int		x_c;
	int		y_c;
	double	r;
	int		color;
	t_bool	border_only;
}	t_circle;

typedef struct s_rectangle {
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
	t_bool	border_only;
}	t_rectangle;

/* Parsing */
void		*fract_sets(char *set);
void		check_args(int argc, char **argv);
void		ft_error(const char *ft_name);

/* Data initialisation and destruction for mlx */
void		free_n_destroy(t_image *image, t_display *display);
t_image		*init_image(t_display *display, int nb_boids);
t_display	*init_display(char *win_name, char **argv);

/* Events handling functions */
int			loop_handler(t_image *image);
int			keys_handler(int key_sym, t_image *image);
int			pointer_handler(int x, int y, t_image *image);
int			button_handler(int button, int x, int y, t_image *image);
int			red_cross_handler(t_image *image);

/* Drawing functions */
void		draw_pixel(t_image *image, size_t x, size_t y, int color);
int			clear_window(t_image *image, int color);
void		clear_window_fade(t_image *image);

/* Colouring functions */
int			get_pixel_color(size_t x, size_t y, t_image *image);
int			color_monochrome(int n, char color);
int			color_bnw(int n, int max_iter);
int			color_grayscale(int n, int max_iter);
int			color_multi(int n, int max_iter);
int			color_lagoon(int n, int max_iter);
int			color_flame(int n, int max_iter);
int			color_r(int n, int max_iter);
int			color_g(int n, int max_iter);
int			color_b(int n, int max_iter);

/* Toolbox */
int			max(int a, int b);
t_bool		ft_c_in_charset(char c, char *charset);
t_bool		ft_is_charset(const char *str, char *charset);

/* Boids */
void 		boids_move(t_image *image);

/*
Escape-codes colors
GREEN \033[0;32m
RED \033[1;31m
Magenta \033[0;35m
NC	\033[0m
*/

#endif
