/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 04:11:28 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/29 05:04:25 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		***ft_mallocwriting(t_line *line)
{
	int		***coo;
	int		a;

	coo = (int***)malloc(sizeof(int**) * line->line);
	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		coo[line->line - 1] = (int**)malloc(sizeof(int*) * line->sizeline);
		while (a < line->sizeline)
		{
			coo[line->line - 1][a] = ft_param(line->vector[a], 0, 0);
			++a;
		}
		line = line->next;
	}
	return (coo);
}

void	ft_freewriting(int ***coo, t_line *line)
{
	int		a;

	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		while (a < line->sizeline)
		{
			free(coo[line->line - 1][a]);
			++a;
		}
		free(coo[line->line - 1]);
		line = line->next;
	}
}

int		assignwr(int **a, int ***coo, t_line *line, int choice)
{
	if (choice == 1 && !(a[1][4] = 0))
	{
		a[1][5] = 0;
		if (a[0][1])
			a[1][4] = (a[0][1] == 1) ? line->vector[*a[0]][4] :
				line->vector[*a[0]][5];
		a[1][0] = coo[line->line - 1][*a[0]][2];
		a[1][2] = coo[line->line - 1][*a[0]][3];
		return (1);
	}
	if (choice == 2 && ((a[1][1] = coo[line->line][*a[0]][2]) || 1))
	{
		a[1][3] = coo[line->line][*a[0]][3];
		if (a[0][1])
			a[1][5] = (a[0][1] == 1) ? line->next->vector[*a[0]][4] :
				line->next->vector[*a[0]][5];
	}
	if (choice == 3 && ((a[1][1] = coo[line->line - 1][*a[0] + 1][2]) || 1))
	{
		a[1][3] = coo[line->line - 1][*a[0] + 1][3];
		if (a[0][1])
			a[1][5] = (a[0][1] == 1) ? line->vector[*a[0] + 1][4] :
				line->vector[*a[0] + 1][5];
	}
	return (1);
}

void	writing(void **all, t_line *ln, int color)
{
	int		***coo;
	int		xabyab[7];
	int		*a[2];

	a[0] = (int[2]){-1, color};
	a[1] = xabyab;
	coo = ft_mallocwriting(ln);
	ln = ft_whichline(1);
	while (ln && (*a[0] = -1))
	{
		while (++*a[0] < ln->sizeline && assignwr(a, coo, ln, 1))
		{
			if (ln->next && *a[0] < ln->next->sizeline &&
					assignwr(a, coo, ln, 2))
				ft_drawline(all, xabyab, color);
			if (*a[0] < ln->sizeline - 1 && assignwr(a, coo, ln, 3))
				ft_drawline(all, xabyab, color);
		}
		ln = ln->next;
	}
	ft_freewriting(coo, ln);
}
