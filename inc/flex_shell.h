/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flex_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 03:04:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEX_SHELL_H

/*
** define
*/
# define FLEX_SHELL_H

# define PATH_SIZE				256
# define LINE_SIZE				1024
# define KEY_BUF_SIZE			6

# ifndef SIGINFO
#	define SIGINFO				29
# endif

# define K_UP					"\x1b\x5b\x41\x0\x0\x0"
# define K_DOWN					"\x1b\x5b\x42\x0\x0\x0"
# define K_RIGHT				"\x1b\x5b\x43\x0\x0\x0"
# define K_LEFT					"\x1b\x5b\x44\x0\x0\x0"
# define K_START				"\x1b\x4f\x48\x0\x0\x0"
# define K_END					"\x1b\x4f\x46\x0\x0\x0"
# define K_DEL					"\x1b\x5b\x33\x7e\x0\x0"
# define K_RETURN				"\xa\x0\x0\x0\x0\x0"
# define K_BACKSPACE			"\x7f\x0\x0\x0\x0\x0"
# define K_ALT_B				"\x1b\x62\x0\x0\x0\x0"
# define K_ALT_F				"\x1b\x66\x0\x0\x0\x0"
# define K_CTRL_UP				"\x1b\x5b\x31\x3b\x35\x41"
# define K_CTRL_DOWN			"\x1b\x5b\x31\x3b\x35\x42"
# define K_CTRL_RIGHT			"\x1b\x5b\x31\x3b\x35\x43"
# define K_CTRL_LEFT			"\x1b\x5b\x31\x3b\x35\x44"
# define K_CTRL_A				"\x1\x0\x0\x0\x0\x0"
# define K_CTRL_E				"\x5\x0\x0\x0\x0\x0"
# define K_CTRL_R				"\x12\x0\x0\x0\x0\x0"
# define K_CTRL_D				"\x4\x0\x0\x0\x0\x0"
# define K_CTRL_L				"\xc\x0\x0\x0\x0\x0"
# define K_CTRL_K				"\xb\x0\x0\x0\x0\x0"
# define K_CTRL_Y				"\x19\x0\x0\x0\x0\x0"
# define K_CTRL_U				"\x15\x0\x0\x0\x0\x0"
# define K_CTRL_P				"\x10\x0\x0\x0\x0\x0"

/*
** include
*/
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h> //redirection + exec.c
# include <fcntl.h> //redirection
# include <time.h> //t_env + bin.c
# include <termios.h>//line_edit (works without...)
# include <term.h> //line_edit
# include <curses.h> //line_edit
# include <sys/ioctl.h> //line_edit + main.c

# include "libft.h"

/*
** enum
*/
enum	e_error
{
	E_NOERROR		= 0, //wtf...
	E_NOEXIT		= (1 << 0),
	E_CMDNOTFOUND	= (1 << 1),
	E_NOSUCHFILE	= (1 << 2),
	E_OPEN			= (1 << 3),
	E_PIPE			= (1 << 4),
	E_FORK			= (1 << 5),
	E_ARG			= (1 << 6),
	E_PATH			= (1 << 7),
	E_TTY			= (1 << 8),
	E_GETATTR		= (1 << 9),
	E_SETATTR		= (1 << 10),
	E_TERM			= (1 << 11)
};

enum	e_status //TODO: rename
{
	KEEP_TRYING,
	KEEP_READING,
	STOP_READING,
	CMD_DONE
};

enum	e_separator
{
	S_WORD = -42,
	S_LINE = -43
};

/*
** struct def
*/
typedef struct s_cursor	t_cursor; //TODO: rename
struct	s_cursor
{
	size_t	prompt_len;
	t_lst	*first_l;
	t_lst	*current_l;
	t_lst	*save;
	t_lst	*history;
};

typedef struct s_env	t_env;
struct s_env
{
	char	**envp;
	t_bst	*bin_root;
	time_t	last_update;
};

/*
	typedef struct s_env	t_env;
	struct	s_env
	{
	t_lst	*first_l;
	char	**env;
	char	**path;
	char	**builtin;
	};
*/

/*
** BASE
** prompt.c
*/
void				prompt(void);
void				prompt_loop(void);

/*
** error.c
*/
void				error(t_int flag, char *msg);

/*
** exec.c
*/
void				launch_cmd(char **cmd);

/*
** REDIRECTION
*/
char				**spaces_error(char **cmd);
void				simple_right(char **cmd);
void				simple_left(char **cmd);
void				simple_pipe(char **cmd);
void				doble_left(char **cmd);
void				doble_right(char **cmd);
void				error_d_right(char **cmd);
void				error_s_right(char **cmd);
void				error_pipe(char **cmd);
void				redirect(char **cmd, int i);

/*
** BUILTIN
** builtin.c
*/
t_bool				launch_builtin(char **av);

/*
** ft_exit.c
*/
void				ft_exit(char **av);

/*
** ft_env.c
*/
void				ft_env(char **av);
t_bool				syntax_error(char *s);
void				print_env(char **envp);

/*
** ft_cd.c
*/
void				ft_cd(char **av);

/*
** ft_setenv.c
*/
void				ft_setenv(char **ac);

/*
** ft_unsetenv.c
*/
void				ft_unsetenv(char **ac);

/*
** LINE EDIT
** read_stdin.c
*/
t_bool				read_stdin(char **line);
t_bool				handle_pipe(char **line);
enum e_status		do_stuff_with_key(char *buf);

/*
** cursor.c
*/
void				print_line(void);
t_cursor			*get_cursor(void);
void				clean_cursor(void);
char				*to_string(void);

/*
** term.c
*/
/*
	struct termios	*get_old_term(void);
	void			default_term(void);
	void			raw_term(void);
*/
int					get_cursor_col(void);
void				switch_term(void);
int					tputs_output(int i);
struct winsize		*get_term_size(void);

/*
** move_cursor.c
*/
enum e_status		move_left(char *buf);
enum e_status		move_right(char *buf);
enum e_status		move_down(char *buf);
enum e_status		move_up(char *buf);
enum e_status		move_begin(char *buf);
enum e_status		move_end(char *buf);
enum e_status		move_next_word(char *buf);
enum e_status		move_prev_word(char *buf);

/*
**	clear.c
*/
enum e_status		clear_term(char *buf);
void				clear_line(void);

/*
** insert.c
*/
t_lst				*cp(t_lst *link); //TODO: move
enum e_status		insert(char *s);
enum e_status		backspace(char *buf);
enum e_status		del(char *buf);
enum e_status		copy(char *buf);
enum e_status		cut_forward(char *buf);
enum e_status		cut_backward(char *buf);
enum e_status		paste(char *buf);

/*
** history.c
*/
enum e_status		set_history(char *buf);
enum e_status		get_history(char *buf);

/*
** ENV
** env.c
*/
t_env			*get_env_struct(void);
char			*get_env(char *to_get);
char			**arr_find(char **arr, char *to_find);

/*
** setenv.c
*/
void			set_env(char *to_set);

/*
** unsetenv.c
*/
void			unset_env(char *to_unset);

/*
** bin.c
*/
char			*get_full_bin(char *bin);
void			update_bin(t_bool force_update);

#endif
