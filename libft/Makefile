# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 14:17:35 by rgramati          #+#    #+#              #
#    Updated: 2024/03/28 23:06:34 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m

FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1

NAME        := libft.a

SRCS_DIR	:=	srcs
OBJS_DIR	:=	.objs

# CHECK
SRC_CHAR	:=	char/ft_max.c char/ft_isalnum.c char/ft_isalpha.c char/ft_isascii.c char/ft_isdigit.c char/ft_isprint.c char/ft_tolower.c char/ft_toupper.c char/ft_isspace.c char/ft_isupper.c char/ft_islower.c

#LIST
SRC_LIST	:=	link_l/ft_lstadd_back_bonus.c link_l/ft_lstadd_front_bonus.c link_l/ft_lstclear_bonus.c link_l/ft_lstdelone_bonus.c link_l/ft_lstiter_bonus.c link_l/ft_lstlast_bonus.c link_l/ft_lstmap_bonus.c link_l/ft_lstnew_bonus.c link_l/ft_lstsize_bonus.c

# MEMORY
SRC_MEM		:=	memory/ft_bzero.c memory/ft_calloc.c memory/ft_memchr.c memory/ft_memcmp.c memory/ft_memcpy.c memory/ft_memmove.c memory/ft_memset.c memory/ft_free_tab.c

# PRINT
SRC_PRINT	:=	stdout/ft_putchar_fd.c stdout/ft_putendl_fd.c stdout/ft_putnbr_fd.c stdout/ft_putstr_fd.c stdout/ft_itoa.c

# STRING
SRC_STRING	:=	string/ft_strtab.c string/ft_strupp.c string/ft_strlow.c string/ft_strsjoin.c string/ft_wc.c string/ft_strtok.c string/ft_atoi.c string/ft_atof.c string/ft_split.c string/ft_strchr.c string/ft_striteri.c string/ft_strdup.c string/ft_strjoin.c string/ft_strlcat.c string/ft_strlcpy.c string/ft_strlen.c string/ft_strmapi.c string/ft_strncmp.c string/ft_strnstr.c string/ft_strrchr.c string/ft_strtrim.c string/ft_substr.c string/ft_tablen.c

# GNL
SRC_GNL		:=	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

ALL_SRCS	:=	$(SRC_CHAR) $(SRC_LIST) $(SRC_MEM) $(SRC_PRINT) $(SRC_STRING) $(SRC_GNL)
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

CC          := gcc
CFLAGS      := -g -Wall -Wextra -Werror
CPPFLAGS    := -I includes

RM          := rm -f
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r                                                                                       \r"
	@printf "\r$(LBLUE)$(NAME)$(RESET)   [ $(LBLUE)$(NAME)$(RESET)        $(GREEN)DONE $(LBLUE)$(RESET)]$(RESET)\n"

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	@printf "\r$(LBLUE)[$(CMP)$(LBLUE)] $(RESET)Compilation in progress... $(GREEN)$<$(BLUE) [$(RESET)$(CMP)$(BLUE)/$(RESET)$(FILE)$(BLUE)]$(RESET)                        \r"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ 	 -o $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

clean:
	@printf "\r$(LBLUE)$(NAME)$(RESET)   [$(LBLUE) objs files  $(RED)deleted$(RESET) ]$(RESET)\n"
	@$(RM) $(OBJS)

fclean: dclean
	@printf "\r$(LBLUE)$(NAME)$(RESET)   [$(LBLUE) $(NAME)     $(RED)deleted$(RESET) ]$(RESET)\n"
	@$(RM) $(NAME)

dclean: clean
	@printf "\r$(LBLUE)$(NAME)$(RESET)   [$(LBLUE) objs dir    $(RED)deleted$(RESET) ]$(RESET)\n"
	@$(RM) -r $(OBJS_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean dclean re
.SILENT: