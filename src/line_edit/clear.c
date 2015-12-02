/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:44:23 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/02 21:01:37 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_env    *g_env; //TODO: clean these

void	clear_term(void)
{
	t_cursor		*c;

	c = get_cursor();
	move_begin();
	if (tputs(tgetstr("cl", NULL), 0, tputs_output) == ERR)
		;//		error(TPUTS, "cl");
	prompt(g_env);
	print_line();
	move_end();
}
