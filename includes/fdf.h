/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:15:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/10 01:09:11 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <libft.h>
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct		s_line
{
	int				sizeline;
	int				line;
	int				**vector;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

void	ft_drawline(void *mlx, void *win, int *xabyab);
void	writing(void *mlx, void *win, t_line *line);
int		my_key_fct(int keycode, void *pdf);
int		translator(int keycode);
t_line	*ft_createline(int l);
t_line	*ft_whichline(int l);
int		translate(int keycode);
int		transl(int keycode);
int		translate_number(int keycode);
int		ft_atoifdf(char *nb);
int		ft_couleur(int a);
int		*save_vector(int pos, int sizeline, int z);
int		*ft_param(int *vector, int axe, int modif);
int		*rotate(int *vector, int axe);
void	shift(int *vector, int axe);
void	scaling(int *vector, int axe);
int		*matrice_multi(int *first, double *second);


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
