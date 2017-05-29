/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 04:04:24 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/29 04:06:31 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*fakemap(char *map)
{
	if (!map || !*map)
		return (NULL);
	while (*map && !(ft_isdigit(*map)))
		++map;
	return (map);
}

void	ft_attribconvert(int *a, t_line *tmp, char *map)
{
	tmp->vector[a[1]] = (int*)malloc(sizeof(int) * 6);
	tmp->vector[a[1]][0] = 1;
	tmp->vector[a[1]][1] = 3;
	tmp->vector[a[1]][2] = a[1];
	tmp->vector[a[1]][3] = a[2] - 1;
	tmp->vector[a[1]][4] = ft_atoifdf(&map[a[0]]);
	while (map[a[0]] != ' ' && map[a[0]] != '\t' &&
			map[a[0]] != ',' && map[a[0]] != '\n' && map[a[0]])
		++a[0];
	tmp->vector[a[1]][5] = ((map[a[0]] == ',' &&
				ft_isdigit(map[a[0] + 1])) ?
			ft_atoifdf(&map[a[0] + 1]) : 0xFFFFFF);
	while (map[a[0]] != ' ' && map[a[0]] != '\t' &&
			map[a[0]] != '\n' && map[a[0]])
		++a[0];
	++a[1];
}

void	initloopconvert(int *a, t_line **tmp, char *map)
{
	*tmp = ft_whichline(a[2]);
	a[1] = a[0];
	while (map[a[0]] && map[a[0]] != '\n')
	{
		if (ft_isdigit(map[a[0]]) && ++(*tmp)->sizeline)
			while (map[a[0]] != ' ' && map[a[0]] != '\t' &&
					map[a[0]] != '\n' && map[a[0]])
				++a[0];
		else
			++a[0];
	}
}

void	registerconvert(int *a, t_line *tmp, char *map)
{
	if (map[a[0]] == '\n' || !map[a[0]])
	{
		tmp->vector = (int**)malloc(sizeof(int*) * tmp->sizeline);
		a[0] = a[1];
		a[1] = 0;
		while (map[a[0]] && map[a[0]] != '\n')
		{
			if (ft_isdigit(map[a[0]]) ||
					(map[a[0]] == '-' && ft_isdigit(map[a[0] + 1])))
				ft_attribconvert(a, tmp, map);
			else
				++a[0];
		}
		++a[2];
	}
}

t_line	*ft_convert(char *map)
{
	int		*a;
	t_line	*tmp;

	a = (int*)ft_memalloc(3 * sizeof(int));
	a[2] = 1;
	tmp = NULL;
	if (!*(map = fakemap(map)))
		return (NULL);
	while (map[a[0]])
	{
		initloopconvert(a, &tmp, map);
		registerconvert(a, tmp, map);
		if (map[a[0]])
			++a[0];
	}
	free(a);
	return (tmp);
}
