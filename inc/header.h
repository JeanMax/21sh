/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 21:52:51 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

/*
** define
*/
# define HEADER_H
# define PATH_SIZE 128

# define KEY_BUF_SIZE           6

# define K_UP					"\x1b\x5b\x41\x0\x0\x0"
# define K_DOWN					"\x1b\x5b\x42\x0\x0\x0"
# define K_RIGHT				"\x1b\x5b\x43\x0\x0\x0" //OK
# define K_LEFT					"\x1b\x5b\x44\x0\x0\x0" //OK
# define K_START				"\x1b\x4f\x48\x0\x0\x0" //OK
# define K_END					"\x1b\x4f\x46\x0\x0\x0" //OK
# define K_DEL					"\x1b\x5b\x33\x7e\x0\x0"  //OK
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
# define K_F3					"\x1b\x4f\x52\x0\x0\x0" //OK
# define K_F4					"\x1b\x4f\x53\x0\x0\x0" //OK
# define K_F5					"\x1b\x5b\x31\x35\x7e\x0" //OK
# define K_F6					"\x1b\x5b\x31\x37\x7e\x0" //OK
# define K_CTRL_D				"\x4\x0\x0\x0\x0\x0" //OK
# define K_CTRL_L				"\xc\x0\x0\x0\x0\x0" //OK

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

typedef struct s_cursor    t_cursor; //TODO: rename
struct  s_cursor
{
    t_lst   *first_l;
    t_lst   *current_l;
    t_lst   *save;
	int		prompt_len;
};


/*
** BASE
*/
void	prompt(t_env *e);
void	error(char *type, char *msg);
void	get_path(t_env *e);
char	**set_av(char *s1, char *s2, t_env *e, int go);
char	*get_env(char *var, t_env *e);
void	init(int ac, char **ae, t_env *e);
void	launch_cmd(char **cmd, t_env *e);
void	prompt_loop(char **av, t_env *e);


/*
** REDIRECTION
*/
char	**spaces_error(char **cmd);
void	simple_right(char **cmd, t_env *e);
void	simple_left(char **cmd, t_env *e);
void	simple_pipe(char **cmd, t_env *e);
void	doble_left(char **cmd, t_env *e);
void	doble_right(char **cmd, t_env *e);
void	error_d_right(char **cmd, t_env *e);
void	error_s_right(char **cmd, t_env *e);
void	error_pipe(char **cmd, t_env *e);
void	redirect(char **cmd, t_env *e, int i);


/*
** BUILTIN
*/
int		is_builtin(char **cmd, t_env *e);
void	launch_builtin(char **av, t_env *e);
void	ft_exit(int ac, char **av);
void	ft_env(char **av, t_env *e);
void	ft_cd(char **av, t_env *e);
void	ft_setenv(char **ac, t_env *e);
void	ft_unsetenv(char **ac, t_env *e);



/*
** LINE EDITION
*/
/*
**  read_stdin.c
*/
t_bool      read_stdin(char **line);
t_bool      handle_pipe(char **line);


/*
** cursor.c
*/
void			print_line(void);
t_cursor		*get_cursor(void);
void			clean_cursor(void);
char			*to_string(void);

/*
** term.c
*/
/*
struct termios  *get_old_term(void);
void            default_term(void);
void            raw_term(void);
*/
int				get_cursor_col(void);
void            switch_term(void);
int             tputs_output(int i);
struct winsize  *get_term_size(void);

/*
** move_cursor.c
*/
void			move_left(void);
void			move_right(void);
void			move_down(void);
void			move_up(void);
void			move_begin(void);
void			move_end(void);
void			move_next_word(void);
void			move_prev_word(void);

/*
**  clear.c
*/
void			clear_term(void);

/*
** insert.c
*/
void			insert(char *s);
void			backspace(void);
void			del(void);
void            copy(void);
void            cut_forward(void);
void            cut_backward(void);
void            paste(void);

#endif
