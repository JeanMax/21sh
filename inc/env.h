/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 17:58:07 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/14 13:20:06 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H

/*
** define
*/
# define ENV_H

/*
** include
*/
# include "flex_shell.h"

/*
** env.c
*/
char			**arr_find(char **arr, char *to_find);

/*
** bin_table.c
*/
void			init_table(t_htable **table);


#endif
