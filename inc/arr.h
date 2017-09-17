/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 18:23:18 by mcanal            #+#    #+#             */
/*   Updated: 2017/09/17 18:23:19 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARR_H
# define ARR_H

# include "libft.h"

void		ft_arr_del(char ***arr);
void		ft_arr_delone(char **arr, char *to_del);
char		**ft_arr_dup(char **arr);
char		**ft_str_split(char const *s, char c);

#endif
