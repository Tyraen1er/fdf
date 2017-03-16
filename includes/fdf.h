/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:15:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/03/16 05:31:39 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
# include <math.h>

void	ft_drawline(void *mlx, vpod *win, int *xabyab);
int		my_key_fct(int keycode, void *pdf);
int		translator(int keycode);
int		translate(int keycode);
int		transl(int keycode);
int		translate_number(int keycode);
int		ft_atoihex(char *nb);
void	ft_param(char *commande);

#endif
