#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/09 21:26:32 by mcanal            #+#    #+#              #
#    Updated: 2017/03/19 20:57:43 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		libft.a

CC =		$(shell clang --version >/dev/null 2>&1 && echo clang || echo gcc)
AR =		ar
ARFLAGS =	-rcs
RM =		rm -rf
MKDIR =		mkdir -p
MAKE =		make
MAKEFLAGS =	-j 4

I_DIR =		-I inc/
O_DIR =		obj
VPATH =		arr:bst:hash:int:io:lst1:lst2:mem:str

CFLAGS =	-Wall -Wextra -Werror -O2

ifeq ($(OS), Windows_NT)
  CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CCFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CCFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
	ECHO = echo -e
    CCFLAGS += -D LINUX
  else ifeq ($(UNAME_S), Darwin)
	ECHO = echo
    CCFLAGS += -D OSX
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), unknown)
    UNAME_P = $(shell uname -m)
  endif
  ifeq ($(UNAME_P), x86_64)
    CCFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CCFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CCFLAGS += -D ARM
  endif
endif

C_ARR =		ft_arrnew.c			ft_arrdup.c			ft_arrdel.c			\
			ft_arrpush.c		ft_arrpop.c			ft_arrget.c			\
			ft_arrswap.c		ft_arrequ.c			ft_arrsort.c		\
			ft_arrfind.c		ft_arrmult.c		ft_arrjoin.c		\
			ft_arrslice.c

C_BST =		ft_bstnew.c			ft_bstdelone.c		ft_bstsearch.c		\
			ft_bstfind.c		ft_bstadd.c			ft_bstdel.c			\
			ft_bstmax.c			ft_bstmin.c			ft_bstinorder.c		\
			ft_bstpreorder.c	ft_bstpostorder.c	ft_bstlen.c 		\
			ft_bstavladd.c		ft_bstavldelone.c

C_HASH =	ft_hnew.c			ft_hset.c			ft_hget.c			\
			ft_hdel.c			ft_hdelone.c		ft_hfind.c			\
			ft_hiter.c

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
			fail.c				failn.c				ft_putnbr_fd.c		\
			ft_putdbl.c			ft_putdbl_fd.c		ft_putdbl_clr.c		\
			ft_debugdbl.c

C_LST1 =	ft_lstlast.c		ft_lstdel.c			ft_lstiter.c		\
			ft_lstadd.c			ft_lstaddlast.c		ft_lstlen.c			\
			ft_lstinser.c		ft_lstrplc.c		ft_lstisn.c			\
			ft_lstnew.c			ft_lstmap.c			ft_lstdelone.c		\
			ft_lstfind.c		ft_lstdellink.c		ft_lstat.c

C_LST2 =	ft_ladd.c			ft_laddlast.c		ft_lat.c			\
			ft_linser.c			ft_lswap.c			ft_lfirst.c			\
			ft_lisn.c			ft_liter.c			ft_llast.c			\
			ft_llen.c			ft_lrplc.c			ft_lnew.c			\
			ft_lmap.c			ft_linsert_list.c	ft_ldellink.c		\
			ft_lfind.c			ft_ldel.c			ft_ldelone.c

C_MEM =		ft_bzero.c			ft_memccpy.c		ft_memchr.c			\
			ft_memcmp.c			ft_memcpy.c			ft_memmove.c		\
			ft_memset.c			ft_memalloc.c		ft_memdel.c			\
			ft_realloc.c		ft_swap.c			ft_shellsort.c

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

OBJS =	$(C_ARR:%.c=$(O_DIR)/%.o)		$(C_BST:%.c=$(O_DIR)/%.o)		\
		$(C_HASH:%.c=$(O_DIR)/%.o)		$(C_INT:%.c=$(O_DIR)/%.o)		\
		$(C_IO:%.c=$(O_DIR)/%.o)		$(C_LST1:%.c=$(O_DIR)/%.o)		\
		$(C_LST2:%.c=$(O_DIR)/%.o)		$(C_MEM:%.c=$(O_DIR)/%.o)		\
		$(C_STR:%.c=$(O_DIR)/%.o)

DEPS =  $(OBJS:%.o=%.d)

WHITE = \033[37;01m
RED = \033[31;01m
GREEN =  \033[32;01m
BLUE =  \033[34;01m
BASIC = \033[0m

.PHONY: all debug sanitize clean fclean re

all:
	$(MAKE) $(NAME)

me_cry:
	$(MAKE) $(NAME) \
		"CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra -O2" #-Wcast-qual

debug:
	$(MAKE) $(NAME) "CFLAGS = -g -ggdb"

sanitize:
	$(MAKE) $(NAME) \
		"CFLAGS = -g -ggdb -O2 -fsanitize=address,undefined -ferror-limit=5"

-include $(DEPS)

$(NAME): $(OBJS)
	@$(ECHO) "$(BLUE)$(OBJS) $(WHITE)->$(RED) $@$(BASIC)"
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@$(ECHO) "$(WHITE)arflags:$(BASIC) $(ARFLAGS)"
	@$(ECHO) "$(WHITE)cflags:$(BASIC) $(CFLAGS) $(CCFLAGS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(ECHO) "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"
	$(CC) $(CFLAGS) $(CCFLAGS) $(I_DIR) -MMD -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
	$(MKDIR) $(O_DIR)

clean:
	$(RM) $(O_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
