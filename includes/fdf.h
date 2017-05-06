/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:15:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/06 02:45:00 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <libft.h>
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

void	ft_drawline(void *mlx, void *win, int *xabyab);
int		my_key_fct(int keycode, void *pdf);
int		translator(int keycode);
int		translate(int keycode);
int		transl(int keycode);
int		translate_number(int keycode);
int		ft_atoifdf(char *nb);
int		ft_couleur(int a);
int		*save_vector(int pos, int sizeline, int z);
int		*ft_param(int *vector, int axe, int modif);
int		*rotate(int *vector, int axe);
void	shift(int *vector, int axe);
void	zoom(int *vector, int axe);
int		*matrice_multi(int *first, double *second);

typedef struct	s_line
{
	int			sizeline;
	int			line;
	int			**vector;
	t_line		next;
	t_line		prev;
}				t_line

/*
**	donnée vector :
**
**	taille matrice largeur		-> pour matrice multi
**	taille matice hauteur		-> pour matrice multi
**	x;
**	y;
**	z;
**	color;
*/
#endif
