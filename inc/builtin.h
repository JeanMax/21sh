/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 17:50:10 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/14 18:17:13 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H

/*
** define
*/
# define BUILTIN_H

# define PATH_SIZE				256

/*
** include
*/
# include "flex_shell.h"

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

#endif
