/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:34:11 by mc                #+#    #+#             */
/*   Updated: 2017/04/22 13:36:18 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_H
# define ARR_H

# include "libft.h"

void		ft_arr_del(char ***arr);
void		ft_arr_delone(char **arr, char *to_del);
char		**ft_arr_dup(char **arr);


#endif
