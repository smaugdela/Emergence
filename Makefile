# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 14:22:11 by smagdela          #+#    #+#              #
#    Updated: 2023/07/03 20:07:28 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes	// Check complet de valgrind.
# lsof -i -a -c ircserv  // Check les leaks de fds associes au reseau (sockets).

#################
#       Variables       #
#################

NAME     =	emergence

INCS    = 	emergence.hpp \
			macro.hpp \
			json.hpp \
			class/Particle.hpp \
			class/Settings.hpp \

SRCS    =	main.cpp \
			loop.cpp \
			fps.cpp \
			force.cpp \
			class/Particle.cpp \
			class/Settings.cpp \

OBJS    =       ${SRCS:.cpp=.o}

INCD    =       includes/
SRCD    =       sources/
OBJD    =       objects/

INCS    :=      ${addprefix ${INCD},${INCS}}
OBJS    :=      ${addprefix ${OBJD},${OBJS}}
SRCS    :=      ${addprefix ${SRCD},${SRCS}}

CXX             =		c++
CXXFLAGS        =		-O3 -Wall -Wextra -Werror -lsfml-graphics -lsfml-window -lsfml-system

#################
#       Fancy Stuff     #
#################

GREY    =       \033[0;30m
RED     =       \033[0;31m
GREEN   =       \033[0;32m
YELLOW  =       \033[0;33m
BLUE    =       \033[0;34m
PURPLE  =       \033[0;35m
WHITE   =       \033[0;37m
CYAN    =       \033[0;96m

S_GREY  =       \033[1;30m
S_RED   =       \033[1;31m
S_GREEN =       \033[1;32m
S_YELLOW         =      \033[1;33m
S_BLUE  =       \033[1;34m
S_PURPLE         =      \033[1;35m
S_WHITE =       \033[1;37m
S_CYAN  =       \033[1;96m

BOLD    =       \033[1m
NC      =       \033[0m

# Box Drawing Unicode
# ┌─┬─┐
# │ │ │
# ├─┼─┤
# │ │ │
# └─┴─┘

#############
#       Rules   #
#############

all:    ${NAME}

${OBJD}%.o:     ${SRCD}%.cpp
		@echo '➤ Compiling $@...'
		@mkdir -p ${OBJD}
		@mkdir -p ${OBJD}/class
		@mkdir -p ${OBJD}/commands
		@${CXX} ${CXXFLAGS} -c -o $@ -I${INCD} $<
		@echo '✔ Object file built!'

${NAME}: ${OBJS}
		@echo '➤ Compiling $@...'
		@${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}
		@echo '✔ Binary available!'

clean:
		@echo '➤ Deleting object files...'
		@-rm -rf ${OBJD}
		@echo '✔ Object files deleted!'

fclean: clean
		@echo '➤ Deleting executable...'
		@-rm -rf ${NAME}
		@echo '✔ Executable deleted!'

re:     fclean  all

.PHONY: all clean fclean re