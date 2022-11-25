# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 11:37:44 by mamuller          #+#    #+#              #
#    Updated: 2021/11/15 11:37:44 by mamuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
SRCD		= ./srcs/

# Command to add the source folder prefix (instead of having it added manually to SRC)
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
# for every SRCF file which is an .c file an o file will be created according to the implicit rule (see $(OBJD)%.o: $(SRCD)%.c)
OBJF 		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD 		= $(OBJF:$(OBJD)%.o)

NAME		= so_long
HEADD		= ./incl/
HEADF		= so_long.h

LIBFTD		= ./libft/
LIBFT_OBJD	= objs
LIBFT_SRCD	= srcs/
LIBFTL		= libft.a

LIBFT_OBJF    = ${LIBFTD}${LIBFT_OBJD}/*.o
LIBFT_MAKE    = make -C ${LIBFTD}

UNAME := $(shell uname)

#if to the respective c file in the source directory no matching o file in the object
#directory is available, then create it according to the following rules:
#Note: the object directory will only be created if not existing already. -p flag throws no errors when already there

ifeq ($(UNAME), Linux)
SRC			= so_long.c utils.c requirement_checks_1.c requirement_checks_2.c \
				initializations.c resize_utils.c draw_game.c exit_handling_linux.c
MINILIB_D = ./mlx_linux

$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			make libftmake
			make mlx_all
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) $(LIBFTD)$(LIBFTL) ./mlx_linux/libmlx_Linux.a -L /usr/include/X11/extensions/ -lXext -lX11 -lm
endif

ifeq ($(UNAME), Darwin)
SRC			= so_long.c utils.c requirement_checks_1.c requirement_checks_2.c \
				initializations.c resize_utils.c draw_game.c exit_handling_mac.c
MINILIB_D = ./mlx_mac

$(OBJD)%.o: $(SRCD)%.c 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -Imlx -c -o $@ $<

$(NAME):	${OBJF}
			make libftmake
			make mlx_all
			$(CC) $(CFLAGS) -L $(MINILIB_D) -lmlx -framework OpenGL -L /usr/X11/lib -lXext -lX11 $(SRCF) $(LIBFTD)$(LIBFTL) -o $(NAME)
endif

all:		${NAME}

libftmake:
			${LIBFT_MAKE}

mlx_all:
			cd $(MINILIB_D) && bash ./configure

clean:		
			${RM} ${OBJD}*.o
			make -C ${LIBFTD} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFTD}${LIBFTL}
			${RM} ${HEADD}so_long.h.gch

re:			fclean all

.PHONY:		all clean fclean re