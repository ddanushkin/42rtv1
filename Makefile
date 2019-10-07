# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lglover <lglover@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 09:56:17 by lglover           #+#    #+#              #
#    Updated: 2019/08/26 15:11:47 by lglover          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = RTv1
INCLUDES = 	-I ./libft/include \
			-I ./sdl2/SDL2.framework/Headers \
			-I ./include

SRC_PATH =	src
SRC_LIST =	app.c \
			cone.c \
            init.c \
            material.c \
            tracer.c \
            vector_math.c \
           	cylinder.c \
           	light.c \
           	pixel.c \
           	ray.c \
           	scene_add.c \
           	utils.c \
           	vector_utils.c \
           	color.c \
           	events.c \
           	main.c \
           	plane.c \
           	sphere.c \
           	vector.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_LIST))

OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_LIST))

LIBFT_PATH = libft
LIBFT = -L $(LIBFT_PATH) -lft

LIBS = 	-lm \
		-lpthread \
		-F ./sdl2 -framework SDL2

YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

.PHONY: all

all: make_libft intro make_obj $(NAME)
	@echo "$(PURPLE)MAKE $(NAME) Done!$(NC)"

intro:
	@echo "\n$(PURPLE)MAKE $(NAME) Start!$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "$(YELLOW)$(NAME): $(notdir $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

make_obj :
	@mkdir -p obj

make_libft :
	@make -C ./libft/

clean :
	@echo "$(YELLOW)Objects Deleted.$(NC)"
	@/bin/rm -rf $(OBJ_PATH)

fclean :	clean
	@echo "$(YELLOW)$(NAME) Deleted.$(NC)"
	@/bin/rm -f $(NAME)

re :	fclean all

rc :
	make -C $(LIBFT_PATH) fclean && make fclean && make