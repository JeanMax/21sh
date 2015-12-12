/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flex_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/12 22:20:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLEX_SHELL_H

/*
** define
*/
# define FLEX_SHELL_H

# define PATH_SIZE				128
# define LINE_SIZE				1024
# define KEY_BUF_SIZE			6

# define K_UP					"\x1b\x5b\x41\x0\x0\x0"
# define K_DOWN					"\x1b\x5b\x42\x0\x0\x0"
# define K_RIGHT				"\x1b\x5b\x43\x0\x0\x0" //OK
# define K_LEFT					"\x1b\x5b\x44\x0\x0\x0" //OK
# define K_START				"\x1b\x4f\x48\x0\x0\x0" //OK
# define K_END					"\x1b\x4f\x46\x0\x0\x0" //OK
# define K_DEL					"\x1b\x5b\x33\x7e\x0\x0"	//OK
# define K_RETURN				"\xa\x0\x0\x0\x0\x0"
# define K_BACKSPACE			"\x7f\x0\x0\x0\x0\x0" //OK
# define K_ALT_B				"\x1b\x62\x0\x0\x0\x0" //OK
# define K_ALT_F				"\x1b\x66\x0\x0\x0\x0" //OK
# define K_CTRL_UP				"\x1b\x5b\x31\x3b\x35\x41" //OK
# define K_CTRL_DOWN			"\x1b\x5b\x31\x3b\x35\x42" //OK
# define K_CTRL_RIGHT			"\x1b\x5b\x31\x3b\x35\x43" //OK
# define K_CTRL_LEFT			"\x1b\x5b\x31\x3b\x35\x44" //OK
# define K_CTRL_A				"\x1\x0\x0\x0\x0\x0" //OK
# define K_CTRL_E				"\x5\x0\x0\x0\x0\x0" //OK
# define K_CTRL_R				"\x12\x0\x0\x0\x0\x0"
# define K_CTRL_D				"\x4\x0\x0\x0\x0\x0" //OK
# define K_CTRL_L				"\xc\x0\x0\x0\x0\x0" //OK
# define K_CTRL_K				"\xb\x0\x0\x0\x0\x0" //OK
# define K_CTRL_Y				"\x19\x0\x0\x0\x0\x0" //OK
# define K_CTRL_U				"\x15\x0\x0\x0\x0\x0" //OK
# define K_CTRL_P				"\x10\x0\x0\x0\x0\x0" //OK

/*
** include
*/
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

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

/*
** struct def
*/
typedef struct s_env	t_env;
struct	s_env
{
	t_lst	*first_l;
	char	**env;
	char	**path;
	char	**builtin;
};

typedef struct s_cursor	t_cursor; //TODO: rename
struct	s_cursor
{
	size_t	prompt_len;
	t_lst	*first_l;
	t_lst	*current_l;
	t_lst	*save;
	t_lst	*history;
};

/*
** BASE
*/
void				prompt(t_env *e);
void				error(t_int flag, char *msg);
void				get_path(t_env *e);
char				**set_av(char *s1, char *s2, t_env *e, int go);
char				*get_env(char *var, t_env *e);
void				init(int ac, char **ae, t_env *e);
void				launch_cmd(char **cmd, t_env *e);
void				prompt_loop(char **av, t_env *e);

/*
** REDIRECTION
*/
char				**spaces_error(char **cmd);
void				simple_right(char **cmd, t_env *e);
void				simple_left(char **cmd, t_env *e);
void				simple_pipe(char **cmd, t_env *e);
void				doble_left(char **cmd, t_env *e);
void				doble_right(char **cmd, t_env *e);
void				error_d_right(char **cmd, t_env *e);
void				error_s_right(char **cmd, t_env *e);
void				error_pipe(char **cmd, t_env *e);
void				redirect(char **cmd, t_env *e, int i);

/*
** BUILTIN
*/
int					is_builtin(char **cmd, t_env *e);
void				launch_builtin(char **av, t_env *e);
void				ft_exit(int ac, char **av);
void				ft_env(char **av, t_env *e);
void				ft_cd(char **av, t_env *e);
void				ft_setenv(char **ac, t_env *e);
void				ft_unsetenv(char **ac, t_env *e);

/*
** LINE EDITION
*/
/*
**	read_stdin.c
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

#endif
