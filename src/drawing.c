/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 03:59:10 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/29 04:09:26 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zminmax(t_line *line)
{
	int		a;
	int		z[2];

	line = ft_whichline(1);
	z[0] = line->vector[0][4];
	z[1] = z[0];
	while (line)
	{
		a = -1;
		while (++a < line->sizeline)
		{
			if (line->vector[a][4] < z[0])
				z[0] = line->vector[a][4];
			if (z[1] < line->vector[a][4])
				z[1] = line->vector[a][4];
		}
		line = line->next;
	}
	ft_color(NULL, z, 0);
}

void	initcolor(int *xabyab, int color, int *a)
{
	a[3] = (color == 1) ? 0xFF << ((xabyab[5] - a[0]) * a[1]) / 1000 :
		xabyab[5];
	a[2] = (color == 1) ? 0xFF << ((xabyab[4] - a[0]) * a[1]) / 1000 :
		xabyab[4];
	a[4] = (a[2] >> 16) & 0xFF;
	a[5] = (a[2] >> 8) & 0xFF;
	a[6] = a[2] & 0xFF;
	a[7] = (a[3] >> 16) & 0xFF;
	a[8] = (a[3] >> 8) & 0xFF;
	a[9] = a[3] & 0xFF;
	if (pow((xabyab[0] - xabyab[1]), 2) + pow((xabyab[2] - xabyab[3]), 2))
	{
		a[7] = (1000 * (a[4] - a[7])) / sqrt(pow((xabyab[0] - xabyab[1]),
					2) + pow((xabyab[2] - xabyab[3]), 2));
		a[8] = (1000 * (a[5] - a[8])) / sqrt(pow((xabyab[0] - xabyab[1]),
					2) + pow((xabyab[2] - xabyab[3]), 2));
		a[9] = (1000 * (a[6] - a[9])) / sqrt(pow((xabyab[0] - xabyab[1]),
					2) + pow((xabyab[2] - xabyab[3]), 2));
	}
	a[4] *= 1000;
	a[5] *= 1000;
	a[6] *= 1000;
}

void	underfortyfive(void **all, int *xabyab, int *a)
{
	while ((a[3] == 1 && a[1] < xabyab[3]) ||
			(a[3] == -1 && xabyab[3] < a[1]))
	{
		if (((xabyab[1] - xabyab[0]) * a[1]) / (xabyab[3] - xabyab[2]) !=
				((xabyab[1] - xabyab[0]) * (a[1] - 1)) /
				(xabyab[3] - xabyab[2]))
			a[0] += a[2];
		mlx_pixel_put(all[0], all[1], a[0], a[1], ft_color(NULL, NULL, 0));
		a[1] += a[3];
	}
}

int		ft_color(int *xabyab, int *z, int color)
{
	static int	a[10] = {0};

	if (z)
	{
		a[0] = z[0];
		if (z[1] != z[0])
			a[1] = 16 * 1000 / (z[1] - z[0]);
		return (0);
	}
	if (xabyab)
	{
		initcolor(xabyab, color, a);
		return (0);
	}
	a[4] -= a[7];
	a[5] -= a[8];
	a[6] -= a[9];
	return (((a[4] / 1000) << 16) | ((a[5] / 1000) << 8) | (a[6]) / 1000);
}

void	ft_drawline(void **all, int *xabyab, int color)
{
	int		*a;

	a = (int[4]){xabyab[0], xabyab[2], (xabyab[0] < xabyab[1]) ? 1 : -1,
		(xabyab[2] < xabyab[3]) ? 1 : -1};
	ft_color(xabyab, NULL, color);
	if (!(xabyab[1] - xabyab[0]) && !(xabyab[3] - xabyab[2]))
		mlx_pixel_put(all[0], all[1], a[0], a[1], ft_color(NULL, NULL, 0));
	else if (abs(xabyab[0] - xabyab[1]) < abs(xabyab[2] - xabyab[3]))
		underfortyfive(all, xabyab, a);
	else
		while ((a[2] == 1 && a[0] < xabyab[1]) ||
				(a[2] == -1 && xabyab[1] < a[0]))
		{
			if (((xabyab[3] - xabyab[2]) * a[0]) / (xabyab[1] - xabyab[0]) !=
					((xabyab[3] - xabyab[2]) * (a[0] - 1)) /
					(xabyab[1] - xabyab[0]))
				a[1] += a[3];
			mlx_pixel_put(all[0], all[1], a[0], a[1], ft_color(NULL, NULL, 0));
			a[0] += a[2];
		}
}
