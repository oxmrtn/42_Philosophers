# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 12:24:28 by mtrullar          #+#    #+#              #
#    Updated: 2024/08/28 10:17:43 by mtrullar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	--no-print-directory

NAME		=	philo
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g3

#Folders
INCLUDE		=	incs/
SRCS_DIR	=	srcs/
OBJ_DIR		=	obj/

RM			=	@rm -rf

#Colors
DEF_COLOR	=	\033[0;39m
GRAY		= 	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

BOLD		=	\033[1m
RESET		=	\033[0m

RESET_LINE	=	\033[A\033[K

SRC_FILE	=	main.c				\
				parsing.c			\
				utils.c				\
				utils_bis.c			\
				init_philo.c		\
				routine.c			\
				states.c			\
				free_func_error.c	\


SRCS		= 	$(addprefix $(SRCS_DIR), $(SRC_FILE))
OBJ			= 	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF		=	.cache_exists

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) -I$(INCLUDE) $(OBJ)
	@echo "$(RESET_LINE)$(MAGENTA)$(BOLD)[ PHILOSOPHER ]$(RESET)$(DEF_COLOR) COMPILED $(GREEN) ✔ $(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(RESET_LINE)$(MAGENTA)$(BOLD)[ PHILOSOPHER ]$(RESET)$(DEF_COLOR)	compiling: $< $(GREEN) ✔ $(DEF_COLOR)"

$(OBJF):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "\n$(RESET_LINE)$(CYAN)Object files cleared$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RESET_LINE)$(CYAN)Everything cleared!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)\e[1mEverything has been rebuilt, fresh and clean\e[0m$(DEF_COLOR)"

.PHONY: all clean fclean re