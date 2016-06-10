#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2016/06/10 18:22:28 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	21sh

C_SRC =	main.c				error.c				prompt.c			\
		exec.c
C_BUI =	builtin.c			ft_exit.c			ft_env.c			\
		ft_unsetenv.c		ft_cd.c				ft_setenv.c
C_RED =	redirection.c		output_redirect.c	dup_fd.c			\
		pipeline.c			input_redirect.c	here_doc.c			\
		util.c
C_LIN = clear.c				cursor.c			insert.c			\
		move_cursor.c		read.c				term.c				\
		get_history.c		read_tty.c			read_notty.c		\
		print_line.c		to_string.c			copy_paste.c		\
		move_cursor_far.c	set_history.c
C_ENV = bin.c				env.c				setenv.c			\
		unsetenv.c

O_DIR = obj
C_DIR = src
VPATH =	src:src/builtin:src/redirection:src/line_edit:src/env

SRCC = 	$(C_SRC:%.c=src/%.c)		$(C_BUI:%.c=src/builtin/%.c)	\
		$(C_ENV:%.c=src/env/%.c)	$(C_LIN:%.c=src/line_edit/%.c)	\
		$(C_RED:%.c=src/redirection/%.c) 
OBJS =	$(C_SRC:%.c=$(O_DIR)/%.o)	$(C_BUI:%.c=$(O_DIR)/%.o)		\
		$(C_ENV:%.c=$(O_DIR)/%.o)	$(C_LIN:%.c=$(O_DIR)/%.o)		\
		$(C_RED:%.c=$(O_DIR)/%.o)
DEPS =  $(OBJS:%.o=%.d)

LIB =		libft/libft.a
TERMCAPS =	-lncurses
I_DIR =		-I./libft/inc/ -I./inc/
MAKE =		make -j
RM =		rm -rf
MKDIR =		mkdir -p
CC =		$(shell clang --version >/dev/null 2>&1 && echo clang || echo gcc)
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
	@$(MAKE) $(NAME) "CFLAGS = -g -ggdb"

sanitize:
	@$(MAKE) -C libft sanitize
	@$(MAKE) $(NAME) \
		"CFLAGS = -g -ggdb -O2 -fsanitize=address,undefined -ferror-limit=5"

me_cry:
	@$(MAKE) -C libft
	@$(MAKE) $(NAME) \
		"CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra -O2" #-Wcast-qual

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
