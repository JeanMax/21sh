/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:02:34 by mcanal            #+#    #+#             */
/*   Updated: 2016/09/27 23:43:25 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H

/*
** define
*/
# define LINE_EDIT_H

# define LINE_SIZE		1024
# define KEY_BUF_SIZE	6

# define K_RETURN		"\xa\x0\x0\x0\x0\x0"
# define K_BACKSPACE	"\x7f\x0\x0\x0\x0\x0"
# define K_DEL			"\x1b\x5b\x33\x7e\x0\x0"
# define K_CTRL_U		"\x15\x0\x0\x0\x0\x0"
# define K_CTRL_D		"\x4\x0\x0\x0\x0\x0"
# define K_CTRL_A		"\x1\x0\x0\x0\x0\x0"
# define K_CTRL_E		"\x5\x0\x0\x0\x0\x0"
# define K_CTRL_R		"\x12\x0\x0\x0\x0\x0"
# define K_CTRL_L		"\xc\x0\x0\x0\x0\x0"
# define K_CTRL_K		"\xb\x0\x0\x0\x0\x0"
# define K_CTRL_P		"\x10\x0\x0\x0\x0\x0"
# define K_ALT_B		"\x1b\x62\x0\x0\x0\x0"
# define K_ALT_F		"\x1b\x66\x0\x0\x0\x0"
# define K_UP			"\x1b\x5b\x41\x0\x0\x0"
# define K_DOWN			"\x1b\x5b\x42\x0\x0\x0"
# define K_RIGHT		"\x1b\x5b\x43\x0\x0\x0"
# define K_LEFT			"\x1b\x5b\x44\x0\x0\x0"

/*
** there is actually an extra \xa on these... meh
*/
#  define K_CTRL_UP		"\x1b\x5b\x31\x3b\x35\x41"
#  define K_CTRL_DOWN	"\x1b\x5b\x31\x3b\x35\x42"
#  define K_CTRL_RIGHT	"\x1b\x5b\x31\x3b\x35\x43"
#  define K_CTRL_LEFT	"\x1b\x5b\x31\x3b\x35\x44"

# ifdef LINUX
#  define K_START		"\x1b\x4f\x48\x0\x0\x0"
#  define K_END			"\x1b\x4f\x46\x0\x0\x0"
#  define K_CTRL_Y		"\x19\x0\x0\x0\x0\x0"
# else
#  define K_START		K_CTRL_A
#  define K_END			K_CTRL_E

/*
** ok, this is actually C-h
*/
#  define K_CTRL_Y		"\x8\x0\x0\x0\x0\x0"
# endif

/*
** include
*/
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>
# include "flex_shell.h"

/*
** enum
*/
enum					e_status
{
	KEEP_TRYING,
	KEEP_READING,
	STOP_READING,
	CMD_DONE
};

enum					e_mismatch
{
	QUOTE = 0,
	D_QUOTE = 1,
	B_QUOTE = 2,
	BRACKET = 3,
	C_BRACKET = 4,
	R_BRACKET = 5,
	MIS_SIZE = 6
};

/*
** struct def
*/
typedef struct s_cursor	t_cursor;
struct					s_cursor
{
	size_t	prompt_len;
	t_lst	*first_l;
	t_lst	*current_l;
	t_lst	*save;
	t_lst	*history;
};

/*
** LINE EDIT
** read.c
*/
enum e_status			do_stuff_with_key(char *buf);
char					*read_loop(char *buf, enum e_status status);

/*
** print_line.c
*/
enum e_status			print_line(void);

/*
** to_string.c
*/
char					*to_string(void);

/*
** cursor.c
*/
t_lst					*cp(t_lst *link);
t_cursor				*get_cursor(void);
void					clean_cursor(void);

/*
** term.c
*/
int						get_cursor_col(void);
void					switch_term(void);
int						tputs_output(int i);
struct winsize			*get_term_size(void);

/*
** move_cursor.c
*/
enum e_status			move_left(char *buf);
enum e_status			move_right(char *buf);
enum e_status			move_down(char *buf);
enum e_status			move_up(char *buf);

/*
** move_cursor_far.c
*/
enum e_status			move_begin(char *buf);
enum e_status			move_end(char *buf);
enum e_status			move_next_word(char *buf);
enum e_status			move_prev_word(char *buf);

/*
**	clear.c
*/
enum e_status			clear_term(char *buf);
void					clear_line(void);

/*
** insert.c
*/
enum e_status			insert(char *s);
enum e_status			backspace(char *buf);
enum e_status			del(char *buf);

/*
** copy_paste.c
*/
enum e_status			copy(char *buf);
enum e_status			cut_forward(char *buf);
enum e_status			cut_backward(char *buf);
enum e_status			paste(char *buf);

/*
** get_history.c
*/
enum e_status			get_history(char *buf);

/*
** set_history.c
*/
enum e_status			set_history(char *buf);

#endif
