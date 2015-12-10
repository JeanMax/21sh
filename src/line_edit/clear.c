/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:44:23 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/10 04:27:04 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flex_shell.h"

extern t_env	*g_env; //TODO: clean these

enum e_status		clear_term(char *buf)
{
	t_cursor		*c;

	if (memcmp(buf, K_CTRL_L, KEY_BUF_SIZE))
		return (KEEP_TRYING);

	c = get_cursor();
	move_begin(NULL);
	if (tputs(tgetstr("cl", NULL), 0, tputs_output) == ERR)
		;//		error(TPUTS, "cl");
	prompt(g_env);
	print_line();
	move_end(NULL);
	return (KEEP_READING);
}
