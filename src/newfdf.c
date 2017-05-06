/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 01:38:18 by eferrand          #+#    #+#             */
/*   Updated: 2017/05/06 02:43:25 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// refaire le witch fd du gnl

t_line		ft_createline(int l)
{
	t_line	*new;
	if (!(new = malloc(sizeof(t_line))))
		return (NULL);
	new->sizeline = 0;
	new->line = l;
	new->vector = NULL;
	new->next = NULL;;
	new->prev = NULL;
}

t_line		*ft_whichline(int l)
{
	static t_line	begin = NULL;
	t_line			tmp;

	if ((tmp = begin))
		while (tmp->next && tmp->line != y)
			tmp = tmp->next;
	if (!begin || tmp->line != y)
	{
		((!begin) ? begin : tmp->next) = ft_create(x, y, z, color);
		if (tmp)
			tmp->next->prev = tmp;
		tmp = (tmp ? tmp->next : begin);
	}
	return (tmp);
}

t_line		*ft_convert(char *map)
{
	int		a;
	int		b;
	int		l;
	t_line	*line;
	t_line	*tmp;

	a = 0;
	l = 1;
	if (!map || !*map)
		return (NULL);
	while (*map && !(ft_isdigit(*map)))
		++map;
	if (!*map)
		return (NULL);
	while (map[a])
	{
		tmp = ft_whichline(l);
		b = a;
		while (map[a] && map[a] != '\n')
		{
			if (ft_isdigit(map[a]) && ++tmp->sizeline)
				while (map[a] != ' ' && map[a] != '\t' && map[a])
					++a;
		}
		if (map[a] == '\n')
		{
			a = b;
			if (!(tmp->vector = (int**)malloc(sizeof(int*) * tmp->sizeline)))
				return (NULL);
			while (map[a] && map[a] != '\n')
			{
				b = 0;
				if (ft_isdigit(map[a]) && ++b)
				{
					tmp->vector[b - 1] = (int*)malloc(sizeof(int) * 6);
					tmp->vector[b - 1][0] = 1;
					tmp->vector[b - 1][1] = 3;
					tmp->vector[b - 1][2] = b;
					tmp->vector[b - 1][3] = l;
					tmp->vector[b - 1][4] = ft_atoifdf(map[a]);
					while (map[a] != ' ' && map[a] != '\t' &&
							map[a] != ',' && map[a])
						++a;
					tmp->vector[b - 1][5] = ((map[a] == ',' &&
								ft_isdigit(map[a + 1])) ?
							ft_atoifdf(map[a + 1]) : 0xFFFFFF);
				while (map[a] != ' ' && map[a] != '\t' && map[a])
					++a;
				}
			}
			++a;
			++l;
		}
	}
	return (line);
}

int  main()
{
	int		fd;
	int		a;
	char	buf[151];
	char	*map;
	char	*tmp;

	map = ft_memalloc(1);
	if (argc != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((a = read(fd, buf, 150)) && a != -1)
	{
		buf[a] = 0;
		tmp = ft_strjoin(map, buf);
		ft_memdel((void *)&map);
		map = tmp;
	}
	if (a == -1 || ((a = 1) && !(ft_display(ft_convert(map), a))))
		ft_putstr("error read or display\n");
	return (0);
}
