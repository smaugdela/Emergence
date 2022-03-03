# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 15:00:41 by smagdela          #+#    #+#              #
#    Updated: 2022/03/03 15:20:30 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
#	VARIABLES	#
#################

NAME	=	emergence

LIBSD	=	libs/
LIBFTD	=	${addprefix ${LIBSD},libft/}
MLXD	=	${addprefix ${LIBSD},mlx_linux/}
INCD	=	includes/
SRCD	=	sources/
OBJD	=	objects/

LIBFT	:=	${addprefix ${LIBFTD},libft.a}
MLX		:=	${addprefix ${MLXD},libmlx_Linux.a}
LIBS	:=	${LIBFT} ${MLX}
SRCS	=	emergence.c parsing.c ft_utils.c ft_data.c ft_draw.c ft_colouring.c ft_colouring_2.c ft_events.c ft_events_2.c boids_movement.c
OBJS	:=	${addprefix ${OBJD},${SRCS:.c=.o}}
DEPS	:=	${addprefix ${OBJD},${SRCS:.c=.d}}
SRCS	:=	${addprefix ${SRCD},${SRCS}}

CC	=	clang
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAGS	=	-lX11 -lXext -lm -lz
LIBSMK	=	make -C

###################
#	FANCY STUFF   #
###################

GREEN	=	\033[0;32m
RED		=	\033[1;31m
NC		=	\033[0m

WHALE	=	"\n${GREEN}       ::: \n     ___:____     |^\/^| \n   ,'        '.    \  / \n   |  O        \___/  | \n ~^~^~^~^~^~^~^~^~^~^~^~^~\n \n Compilation Successful!	${NC}\n"
NUKE	=	"\n${RED}     _.-^^---....,,--       \n _--                  --_  \n<                        >)\n|                         | \n \._                   _./  \n    '''--. . , ; .--'''       \n          | |   |             \n       .-=||  | |=-.   \n       '-=£€%&%€£=-'   \n          | ;  :|     \n _____.,-£%&€@%£&£~,._____${NC}\n\n"

#############
#	RULES	#
#############

all:	${NAME}

${NAME}:	${LIBS} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${MLXFLAGS} ${LIBS} -o ${NAME}
	@echo ${WHALE}

${OBJD}%.o:	${SRCD}%.c
	mkdir -p ${OBJD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -I${LIBFTD} -I${MLXD} -MMD $<

${LIBS}:
	${LIBSMK} ${LIBFTD} bonus
	${LIBSMK} ${MLXD} all

clean:
	-rm -rf ${OBJD} ${DEPD}
	${LIBSMK} ${LIBFTD} clean
	${LIBSMK} ${MLXD} clean

fclean:	clean
	-rm ${NAME}
	${LIBSMK} ${LIBFTD} fclean
	${LIBSMK} ${MLXD} clean
	@echo ${NUKE}

re:		fclean all

norm:
	norminette ${SRCS} ${INCD}*.h ${LIBFTD}*.c ${LIBFTD}*.h

.PHONY : re all clean fclean norm

-include ${DEPS}
