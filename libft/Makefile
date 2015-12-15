#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/09 21:26:32 by mcanal            #+#    #+#              #
#    Updated: 2015/12/15 02:27:24 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	libft.a

CC =	clang
AR =	ar -rcs
RM =	rm -rf
MKDIR =	mkdir -p

I_DIR =	-I inc/
O_DIR =	obj
VPATH =	bst:int:io:lst1:lst2:mem:str

CFLAGS =	-Wall -Wextra -Werror -Wpedantic -Wshadow -Wcast-align \
			-Wconversion -Wstrict-prototypes -Wmissing-prototypes \
			-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
			-Wstrict-overflow=5 -Waggregate-return -Wunreachable-code \
			-Winit-self -Wold-style-definition -Wpadded -Wredundant-decls -O2 
#-Wcast-qual
C_BST =		ft_bstnew.c			ft_bstfree.c		ft_bstclean.c		\
			ft_bstfind.c		ft_bstadd.c			ft_bstdel.c			\
			ft_bstmax.c			ft_bstmin.c			ft_bstinorder.c		\
			ft_bstpreorder.c	ft_bstpostorder.c	ft_bstlen.c 		\
			ft_bstavladd.c		ft_bstavldel.c		ft_bstsearch.c
C_INT =		ft_isalnum.c		ft_isalpha.c		ft_isxdigit.c		\
			ft_isascii.c		ft_isdigit.c		ft_isprint.c		\
			ft_islower.c		ft_isupper.c		ft_isblank.c		\
			ft_iscntrl.c		ft_isgraph.c		ft_isspace.c		\
			ft_ispunct.c		ft_itoa.c			ft_tolower.c		\
			ft_toupper.c		ft_max.c			ft_min.c			\
			ft_abs.c
C_IO =		ft_putchar.c		ft_putnbr.c			ft_putstr.c			\
			ft_putendl.c		ft_putchar_fd.c		get_all.c			\
			ft_putendl_fd.c		ft_putstr_fd.c		get_next_line.c		\
			ft_putstr_clr.c		ft_putchar_clr.c	ft_putendl_clr.c	\
			ft_debugstr.c		ft_debugnbr.c		ft_putnbr_clr.c		\
			get_line.c			fail.c				failn.c				\
			ft_putnbr_fd.c		ft_putdbl.c			ft_putdbl_fd.c		\
			ft_putdbl_clr.c		ft_debugdbl.c
C_LST1 =	ft_lstlast.c		ft_lstdel.c			ft_lstiter.c		\
			ft_lstadd.c			ft_lstaddlast.c		ft_lstlen.c			\
			ft_lstinser.c		ft_lstrplc.c		ft_lstisn.c			\
			ft_lstnew.c			ft_lstmap.c			ft_lstdelone.c		\
			ft_lstfind.c		ft_lstdellink.c		ft_lstfree.c		\
			ft_lstclean.c		ft_lstat.c
C_LST2 =	ft_ladd.c			ft_laddlast.c		ft_lat.c			\
			ft_linser.c			ft_lclean.c			ft_lfirst.c			\
			ft_lisn.c			ft_liter.c			ft_llast.c			\
			ft_llen.c			ft_lrplc.c			ft_lnew.c			\
			ft_lfree.c 			ft_lfind.c			ft_lswap.c			\
			ft_lmap.c			ft_linsert_list.c	ft_ldellink.c		
C_MEM =		ft_bzero.c			ft_memccpy.c		ft_memchr.c			\
			ft_memcmp.c			ft_memcpy.c			ft_memmove.c		\
			ft_memset.c			ft_memalloc.c		ft_memdel.c			\
			ft_realloc.c		ft_arrdel.c			ft_arrdup.c			\
			ft_swap.c			ft_shellsort.c		ft_arrdelone.c
C_STR =		ft_strindex.c		ft_strrindex.c		ft_strcpy.c			\
			ft_atoi.c			ft_strcat.c			ft_strcmp.c			\
			ft_strdup.c			ft_strlen.c			ft_strncpy.c		\
			ft_strchr.c			ft_strlcat.c		ft_strsplit.c		\
			ft_strncat.c		ft_strncmp.c		ft_strnstr.c		\
			ft_strdel.c			ft_strjoin.c		ft_strnew.c			\
			ft_strequ.c			ft_strmap.c			ft_strrchr.c		\
			ft_striter.c		ft_strmapi.c		ft_strsub.c			\
			ft_strclr.c			ft_striteri.c		ft_strnequ.c		\
			ft_strtrim.c		ft_strndup.c		ft_istoobig.c		\
			ft_strstr.c			
SRCC =	$(C_BST:%.c=bst/%.c)				$(C_INT:%.c=io/%.c)			\
		$(C_IO:%.c=is/%.c)					$(C_LST1:%.c=lst1/%.c)		\
		$(C_LST2:%.c=lst2/%.c)				$(C_MEM:%.c=mem/%.c)		\
		$(C_STR:%.c=str/%.c)		
OBJS =	$(C_BST:%.c=$(O_DIR)/%.o)			$(C_INT:%.c=$(O_DIR)/%.o)	\
		$(C_IO:%.c=$(O_DIR)/%.o)			$(C_LST1:%.c=$(O_DIR)/%.o)	\
		$(C_LST2:%.c=$(O_DIR)/%.o)			$(C_MEM:%.c=$(O_DIR)/%.o)	\
		$(C_STR:%.c=$(O_DIR)/%.o)
DEPS =  $(OBJS:%.o=%.d)

WHITE = \033[37;01m
RED = \033[31;01m
GREEN =  \033[32;01m
BLUE =  \033[34;01m
BASIC = \033[0m

.PHONY: all debug sanitize clean fclean re

all:
	@$(MAKE) $(NAME)

debug: CFLAGS = -g -ggdb -O2
debug: $(NAME)

sanitize: CFLAGS = -g -ggdb -O2 -fsanitize=address,undefined
sanitize: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(BLUE)$(OBJS) $(WHITE)->$(RED) $@$(BASIC)"
	@echo "$(WHITE)ar:$(BASIC) $(AR)"
	@echo "$(WHITE)flags:$(BASIC) $(CFLAGS)"
	@echo "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@echo "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"
	@$(CC) $(CFLAGS) $(I_DIR) -MMD -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
	@$(MKDIR) $(O_DIR)

clean:
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
