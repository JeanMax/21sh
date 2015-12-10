#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2015/12/09 22:30:12 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	21sh

C_SRC =	main.c				error.c				handle_env.c		\
		prompt.c			exec.c				signal.c
C_BUI =	builtin.c			exit.c				env.c				\
		unsetenv.c			cd.c				setenv.c
C_RED =	redirection.c		space_error.c		simple_right.c		\
		simple_left.c		double_right.c		double_left.c		\
		simple_pipe.c		error_s_right.c		error_pipe.c		\
		error_d_right.c
C_LIN = clear.c				cursor.c			insert.c			\
		move_cursor.c		read_stdin.c		term.c				\
		history.c

O_DIR = obj
C_DIR = src
VPATH =	src:src/builtin:src/redirection:src/line_edit

SRCC = 	$(C_SRC:%.c=src/%.c)		$(C_BUI:%.c=src/builtin/%.c)	\
		$(C_RED:%.c=src/redirection/%.c) $(C_LIN:%.c=src/line_edit/%.c)
OBJS =	$(C_SRC:%.c=$(O_DIR)/%.o)	$(C_BUI:%.c=$(O_DIR)/%.o)		\
		$(C_RED:%.c=$(O_DIR)/%.o)	$(C_LIN:%.c=$(O_DIR)/%.o)	
DEPS =  $(OBJS:%.o=%.d)

LIB =		libft/libft.a
TERMCAPS =	-lncurses
I_DIR =		-I./libft/inc/ -I./inc/
MAKE =		make -j
RM =		rm -rf
MKDIR =		mkdir -p
CC =		clang
CFLAGS =	-Wall -Wextra -Werror -O2

WHITE =	\033[37;01m
RED =	\033[31;01m
GREEN =	\033[32;01m
BLUE =	\033[34;01m
BASIC =	\033[0m

.PHONY: all debug sanitize me_cry clean fclean zclean re brute

all:
	@$(MAKE) -C libft
	@$(MAKE) $(NAME)

debug:
	@$(MAKE) -C libft debug
	@$(MAKE) $(NAME) "CFLAGS = -g -ggdb -O2"

sanitize:
	@$(MAKE) -C libft sanitize
	@$(MAKE) $(NAME) \
		"CFLAGS = -g -ggdb -O2 -fsanitize=address,undefined -ferror-limit=5"

me_cry:
	@$(MAKE) -C libft
	@$(MAKE) $(NAME) \
		"CFLAGS = -Wpedantic -Wshadow -Wcast-qual -Wconversion -Wcast-align \
				  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code \
				  -Winit-self -Wmissing-declarations -Wfloat-equal \
				  -Wbad-function-cast -Wundef -Waggregate-return \
				  -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
				  -Wredundant-decls -Wall -Werror -Wextra -O2"

-include $(DEPS)

$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(I_DIR) $(OBJS) $(LIB) -o $@ $(TERMCAPS)
	@echo "$(BLUE)$(OBJS) $(WHITE)->$(RED) $@ $(BASIC)"
	@echo "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@echo "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@
	@echo "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"

$(OBJS): | $(O_DIR)

$(O_DIR):
	@$(MKDIR) $(O_DIR)

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

zclean: fclean
	@make -C libft fclean

re: fclean all

brute: zclean all
