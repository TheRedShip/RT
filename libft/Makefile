# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 14:17:35 by rgramati          #+#    #+#              #
#    Updated: 2024/05/03 02:30:13 by marvin           ###   ########.fr        #
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

FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1

NAME        := libft.a

SRCS_DIR	:=	srcs

OBJS_DIR	:=	.objs

# CHECK
SRC_CHAR	:=	char/ft_max.c 						\
				char/ft_isalnum.c 					\
				char/ft_isalpha.c 					\
				char/ft_isascii.c 					\
				char/ft_isdigit.c 					\
				char/ft_isprint.c 					\
				char/ft_tolower.c 					\
				char/ft_toupper.c 					\
				char/ft_isspace.c 					\
				char/ft_isupper.c 					\
				char/ft_islower.c

#LIST
SRC_LIST	:=	link_l/ft_lstadd_back_bonus.c		\
				link_l/ft_lstadd_front_bonus.c		\
				link_l/ft_lstclear_bonus.c			\
				link_l/ft_lstdelone_bonus.c			\
				link_l/ft_lstiter_bonus.c			\
				link_l/ft_lstlast_bonus.c			\
				link_l/ft_lstmap_bonus.c			\
				link_l/ft_lstnew_bonus.c			\
				link_l/ft_lstsize_bonus.c

# MEMORY
SRC_MEM		:=	memory/ft_bzero.c 					\
				memory/ft_calloc.c 					\
				memory/ft_memchr.c 					\
				memory/ft_memcmp.c 					\
				memory/ft_memcpy.c 					\
				memory/ft_memmove.c 				\
				memory/ft_memset.c 					\
				memory/ft_free_tab.c

# PRINT
SRC_PRINT	:=	stdout/ft_displays.c				\
				stdout/ft_putendl_fd.c				\
				stdout/ft_itoa.c					\
				stdout/ft_dprintf.c

# STRING
SRC_STRING	:=	string/ft_sort_strs.c				\
				string/ft_strtab.c					\
				string/ft_strupp.c					\
				string/ft_strlow.c					\
				string/ft_strsjoin.c				\
				string/ft_wc.c						\
				string/ft_strtok.c					\
				string/ft_atoi.c					\
				string/ft_atof.c					\
				string/ft_split.c					\
				string/ft_strchr.c					\
				string/ft_striteri.c				\
				string/ft_strdup.c					\
				string/ft_strjoin.c					\
				string/ft_strlcat.c					\
				string/ft_strlcpy.c					\
				string/ft_strlen.c					\
				string/ft_strmapi.c					\
				string/ft_strncmp.c					\
				string/ft_strnstr.c					\
				string/ft_strrchr.c					\
				string/ft_strtrim.c					\
				string/ft_substr.c					\
				string/ft_tablen.c

# GNL
SRC_GNL		:=	get_next_line/get_next_line.c 		\
				get_next_line/get_next_line_utils.c

ALL_SRCS	:=	$(SRC_CHAR) 						\
				$(SRC_LIST)							\
				$(SRC_MEM)							\
				$(SRC_PRINT)						\
				$(SRC_STRING)						\
				$(SRC_GNL)

SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

CC          := cc

CFLAGS      := -Ofast -g -Wall -Wextra -Werror

IFLAGS    := -I includes


RM          := rm -rf

MAKEFLAGS   += --no-print-directory

DIR_DUP     = mkdir -p $(@D)

# RULES ********************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "$(LINE_CLR)$(BWHITE) $(NAME): PROJECT READY !$(RESET)\n"

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	if [ $(CMP) -eq '1' ]; then \
		printf "\n"; \
	fi;
	@printf "$(LINE_CLR)$(WHITE) $(NAME): $(CMP)/$(FILE) $(BWHITE)$<$(RESET) $(GREEN)compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))
	if [ $(CMP) -eq $(FILE) ]; then \
		printf "$(LINE_CLR)$(WHITE) $(NAME): $(CMP)/$(FILE)\n$(LINE_CLR)$(BGREEN) Compilation done !$(RESET)\n"; \
	fi \

clean:
	@$(RM) $(OBJS)

dclean: clean
	@$(RM) $(OBJS_DIR)

fclean: dclean
	@printf " $(BWHITE)$(NAME):$(BRED) cleaned.$(RESET)\n"
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

# **************************************************************************** #

.PHONY: all clean fclean dclean re
.SILENT: