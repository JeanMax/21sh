/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2015/12/15 08:26:50 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H

/*
** define
*/
# define REDIRECTION_H

/*
** include
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "flex_shell.h"

/*
** redirection.c
*/
void				do_redirect(char **cmd, enum e_replacement c, int o_flag, \
						void(*do_stuff_with_cmd_and_fd_now)(char **, int, int));
/*
** dup_fd.c
*/
void				dup_input(char **cmd);
void				dup_output(char **cmd);
void				dup_exec(char **cmd, int *pipe_fd, int fd_left);

/*
** output_redirect.c
*/
void				output_redirect(char **cmd);
void				output_append_redirect(char **cmd);

/*
** input_redirect.c
*/
void				input_redirect(char **cmd);

/*
** pipeline.c
*/
void				pipeline(char **cmd);

/*
** here_doc.c
*/
void				here_doc(char **cmd);

#endif
