/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flex_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/14 13:25:36 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEX_SHELL_H

/*
** define
*/
# define FLEX_SHELL_H

# ifndef SIGINFO
#  define SIGINFO		29
# endif

/*
** include
*/
# include <time.h>
# include "libft.h"
# include "arr.h"

/*
** enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_CMDNOTFOUND = (1 << 1),
	E_NOSUCHFILE = (1 << 2),
	E_OPEN = (1 << 3),
	E_PIPE = (1 << 4),
	E_FORK = (1 << 5),
	E_ARG = (1 << 6),
	E_PATH = (1 << 7),
	E_TTY = (1 << 8),
	E_GETATTR = (1 << 9),
	E_SETATTR = (1 << 10),
	E_TERM = (1 << 11)
};

enum					e_replacement
{
	S_WORD = -42,
	S_LINE = -41,
	R_OUTPUT = -40,
	R_OUTPUT_APPEND = -39,
	R_INPUT = -38,
	R_PIPELINE = -37,
	R_HERE_DOC = -36,
	R_DUP_INPUT = -35,
	R_DUP_OUTPUT = -34
};

/*
** struct def
*/
typedef struct s_env	t_env;
struct					s_env
{
	char				**envp;
	t_htable			*bin_table;
	time_t				last_update;
};

/*
** BASE
** prompt.c
*/
void					prompt(void);
void					prompt_loop(void);

/*
** error.c
*/
void					error(t_uint flag, char *msg);

/*
** exec.c
*/
void					exec_cmd(char **cmd);

/*
** REDIRECTION
** redirection.c
*/
t_bool					exec_redirection(char **cmd);

/*
** BUILTIN
** builtin.c
*/
t_bool					exec_builtin(char **cmd);

/*
** LINE EDIT
** read_tty.c
*/
t_bool					read_tty(char **line);
t_bool					read_tty_brute(char **line);

/*
** read_notty.c
*/
t_bool					read_notty(char **line);
t_bool					read_notty_brute(char **line);

/*
** cursor.c
*/
void					init_cursor(void);
void					finit_cursor(void);


/*
** ENV
** env.c
*/
t_env					*get_env_struct(void);
char					*get_env(char *to_get);

/*
** setenv.c
*/
void					set_env(char *to_set);

/*
** unsetenv.c
*/
void					unset_env(char *to_unset);

/*
** bin.c
*/
char					*get_full_bin(char *bin);
void					update_bin(t_bool force_update);


void					free_string(void *s, size_t n);
void					free_char(void *c, size_t n);
t_bool					fail(const char *s);
t_bool					failn(const char *s);

#endif
