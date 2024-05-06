# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 19:05:58 by marvin            #+#    #+#              #
#    Updated: 2024/05/01 17:03:04 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		=	\033[30;49;3m
RED			=	\033[31;49;3m
GREEN		=	\033[32;49;3m
YELLOW		=	\033[33;49;3m
BLUE		=	\033[34;49;3m
MAGENTA		=	\033[35;49;3m
CYAN		=	\033[36;49;3m
WHITE		=	\033[37;49;3m

BBLACK		=	\033[30;49;3;1m
BRED		=	\033[31;49;3;1m
BGREEN		=	\033[32;49;3;1m
BYELLOW		=	\033[33;49;3;1m
BBLUE		=	\033[34;49;3;1m
BMAGENTA	=	\033[35;49;3;1m
BCYAN		=	\033[36;49;3;1m
BWHITE		=	\033[37;49;3;1m

RESET		=	\033[0m

LINE_CLR	=	\33[2K\r

FILE		=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP			=	1

NAME        :=	miniRT

LFT_DIR 	:=	./libft

MINILIB_DIR := ./mlx

LFT			:=	$(LFT_DIR)/libft.a

MLX			:=	$(MINILIB_DIR)/libmlx.a


SRCS_DIR	:=	srcs

OBJS_DIR	:=	.objs

ASSETS_DIR	:=	assets

SRC_ASSETS_DIR := assets_src 

SRC_ASSETS_NAME	:=	solar_system/saturn.jpg			\
					solar_system/mercury.jpg		\
					solar_system/skybox_stars.jpg	\
					solar_system/mars.jpg			\
					solar_system/moon.jpg			\
					solar_system/jupiter.jpg		\
					solar_system/earth.jpg			\
					solar_system/venus.jpg			\
					portal_map/cube_blue.jpg		\
					portal_map/platform.jpg			\
					portal_map/wall.jpg				\
					portal_map/floor.jpg			\
					portal_map/cube.jpg				\
					billard/billard_1.jpg			\
					billard/billard_2.jpg			\
					billard/billard_3.jpg			\
					billard/billard_4.jpg			\
					billard/billard_5.jpg			\
					billard/billard_6.jpg			\
					billard/billard_7.jpg			\
					billard/billard_8.jpg			\
					billard/billard_9.jpg			\
					billard/billard_10.jpg			\
					billard/billard_11.jpg			\
					billard/billard_12.jpg			\
					billard/billard_13.jpg			\
					billard/billard_14.jpg			\
					billard/billard_15.jpg			\
					thing/skybox.jpg				

SRC_PARSING	:=  parsing/rt_parse.c					\
				parsing/parse_utils.c				\
				parsing/rt_parse_objects.c			\
				parsing/rt_parse_objects2.c			\
				parsing/rt_parse_settings.c			\
				parsing/rt_parse_others.c			\
				parsing/rt_verify_parsing_others.c	\
				parsing/rt_verify_parsing_objects.c	\
				parsing/rt_verify_parsing_objects2.c\
				parsing/rt_verify_parsing_settings.c



SRC_OBJECTS :=	objects/init.c						\
				objects/hit_func.c					\

SRC_WINDOW	:=	window/window.c						\
				window/hook.c						

SRC_RENDER	:=	render/render.c						\
				render/utils.c						\
				render/image.c						\
				render/matrix.c						\
				render/scatter.c					\
				render/light.c

SRC_VECTOR	:=	vector/vec_num3f.c					\
				vector/vec_vec3f.c					\
				vector/vec_utils.c


SRC_POSTPRO :=	postprocess/bloom.c					\
				postprocess/blur.C					\
				postprocess/img_utils.C				\
				postprocess/sample.c			

SRC_MULTI_S	:=	multi_pc/server/server.c			\
				multi_pc/server/handle_clients.c	\
				multi_pc/server/lst_buffer.c		\
				multi_pc/server/lst_threads.c		\
				multi_pc/server/hooks.c				\
				multi_pc/server/mutex.c

SRC_MULTI_C :=	multi_pc/client/rt_to_server.c		


ALL_SRCS	:=	$(SRC_PARSING) $(SRC_OBJECTS)		\
				$(SRC_WINDOW) $(SRC_RENDER)			\
				$(SRC_VECTOR) $(SRC_POSTPRO)		\
				$(SRC_MULTI_S) $(SRC_MULTI_C)		\
				minirt.c
				
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)


OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

ASSETS		:=	$(addprefix $(ASSETS_DIR)/, $(SRC_ASSETS_NAME:%.jpg=%.xpm))

HEADERS		:=	includes/minirt.h

CC          :=	cc

CFLAGS      :=	-Ofast -pthread -g -Wall -Wextra -Werror

IFLAGS	    :=	-I $(LFT_DIR)/includes -I ./includes -I $(MINILIB_DIR)


RM          :=	rm -rf

MAKEFLAGS   += --no-print-directory

DIR_DUP     =	mkdir -p $(@D)

# RULES ********************************************************************** #

all: $(NAME)

$(NAME): $(LFT) $(MLX) $(OBJS) $(HEADERS) $(ASSETS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFT_DIR)/libft.a -Lmlx -lmlx_Linux -I./mlx -lXext -lX11 -lm -lz -o $(NAME)
	@printf "$(LINE_CLR)$(BWHITE) $(NAME): PROJECT COMPILED !$(RESET)\n\n"

$(MLX):
	@printf "$(BWHITE) $(NAME): $(BWHITE)minilibx compiling...$(RESET)\n"
	@make --quiet -j -C $(MINILIB_DIR) >/dev/null 2>/dev/null

$(LFT):
	@make -j -C $(LFT_DIR)

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	@if [ $(CMP) -eq '1' ]; then \
		printf "\n"; \
	fi;
	@printf "$(LINE_CLR)$(WHITE) $(NAME): $(CMP)/$(FILE) $(BWHITE)$<$(RESET) $(GREEN)compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))
	@if [ $(CMP) -gt $(FILE) ]; then \
		printf "$(LINE_CLR)$(WHITE) $(NAME): $$(($(CMP)-1))/$(FILE)\n$(LINE_CLR)$(BGREEN) Compilation done !$(RESET)\n"; \
	fi \


$(ASSETS_DIR)/%.xpm: assets_src/%.jpg
	@mkdir -p $(dir $@)
	@convert $< $@ & 

clean:
	@$(RM) $(OBJS)

dclean: clean
	@$(RM) $(OBJS_DIR)

fclean: dclean
	@make --quiet clean -C ${MINILIB_DIR}
	@printf " $(BWHITE)$(NAME):$(BRED) cleaned.$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LFT_DIR) fclean
	@killall convert 2>/dev/null > /dev/null|| true && \
	sleep 0.5 && rm -rf $(ASSETS_DIR)&

re:
	@$(MAKE) fclean
	@$(MAKE) all

# **************************************************************************** #

.PHONY: all clean fclean dclean re
