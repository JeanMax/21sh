/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:44:23 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 22:35:25 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

extern t_env	*g_env; //TODO: clean these

void				clear_line(void)
{
	t_lst		*tmp;
	size_t		count;

	count = get_cursor()->prompt_len;
	tmp = get_cursor()->first_l;
	tputs(tgetstr("sc", NULL), 0, tputs_output);
	tputs(tgetstr("ce", NULL), 0, tputs_output);
	while (tmp)
	{
		if (!(++count % get_term_size()->ws_col))
		{
			tputs(tgetstr("cd", NULL), 0, tputs_output);
				;
			break ;
		}
		tmp = tmp->next;
	}
	tputs(tgetstr("rc", NULL), 0, tputs_output);
}

enum e_status		clear_term(char *buf)
{
	t_cursor		*c;

	if (memcmp(buf, K_CTRL_L, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	move_begin(NULL);
	tputs(tgetstr("cl", NULL), 0, tputs_output);
	prompt(g_env);
	print_line();
	move_end(NULL);
	return (KEEP_READING);
}
