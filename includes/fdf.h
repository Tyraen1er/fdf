/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 04:15:31 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/29 05:06:52 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

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

typedef struct		s_line
{
	int				sizeline;
	int				line;
	int				**vector;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

int		***ft_mallocwriting(t_line *line);
int		assignwr(int **a, int ***coo, t_line *line, int choice);
char	*fakemap(char *map);
void	writing(void **all, t_line *line, int color);
void	initcolor(int *xabyab, int color, int *a);
void	calculrotate(int **ret, double *rot);
void	underfortyfive(void **all, int *xabyab, int *a);
void	ft_attribconvert(int *a, t_line *tmp, char *map);
void	initloopconvert(int *a, t_line **tmp, char *map);
void	registerconvert(int *a, t_line *tmp, char *map);
void	ft_freewriting(int ***coo, t_line *line);
void	zminmax(t_line *line);
void	ft_drawline(void **all, int *xabyab, int modif);
int		ft_display(t_line *line);
int		my_key_fct(int keycode, void *pdf);
int		translator(int keycode);
t_line	*ft_convert(char *map);
t_line	*ft_createline(int l);
t_line	*ft_whichline(int l);
int		translate(int keycode);
int		transl(int keycode);
int		translate_number(int keycode);
int		ft_atoifdf(char *nb);
int		ft_color(int *xabyab, int *z, int modif);
int		*save_vector(int pos, int sizeline, int z);
int		*ft_param(int *vector, int axe, int modif);
int		*rotate(int *vector, int axe);
void	shift(int *vector, int axe);
void	scaling(int *vector, int axe);
int		*matrice_multi(double *first, int *second);

#endif
