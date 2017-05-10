#include "fdf.h"

t_line      *ft_createline(int l);
int			ft_test(t_line *line);
t_line      *ft_whichline(int l);
t_line      *ft_convert(char *map);
int 	    ft_atoifdf(char *nb);

int     ft_atoifdf(char *nb)
{
	int     ret;
	int     a;
	int     b;

	ret = 0;
	b = 0;
	a = ft_strlen(nb);
	if (nb[b] != '0' || nb[b + 1] != 'x')
		return (atoi(nb));
	while (a--)
	{
		if ('0' <= nb[a] && nb[a] <= '9')
			ret += (nb[a] - '0') << (b * 4);
		if ('a' <= nb[a] && nb[a] <= 'f')
			ret += (nb[a] - 'a' + 10) << (b * 4);
		if ('A' <= nb[a] && nb[a] <= 'F')
			ret += (nb[a] - 'A' + 10) << (b * 4);
		++b;
	}
	return (ret);
}

t_line      *ft_createline(int l)
{
	t_line  *new;

	if (!(new = malloc(sizeof(t_line))))
		return (NULL);
	new->sizeline = 0;
	new->line = l;
	new->vector = NULL;
	new->next = NULL;;
	new->prev = NULL;
	return (new);
}

t_line      *ft_whichline(int l)
{
	static t_line   *begin = NULL;
	t_line          *tmp;

	if ((tmp = begin))
		while (tmp->next && tmp->line != l)
			tmp = tmp->next;
	if (!begin || tmp->line != l)
	{
		if (!begin)
			begin = ft_createline(l);
		else
		{
			tmp->next = ft_createline(l);
			tmp->next->prev = tmp;
		}
		tmp = (tmp ? tmp->next : begin);
	}
	return (tmp);
}

int		ft_test(t_line *line)
{
	int		xabyab[6];
	int		a;
	int		***coo;

	if (!line)
		return (0);
	line = ft_whichline(1);
	while (line)
	{
		printf("sizeline = %d line = %d\n", line->sizeline,  line->line);
		a = 0;
		while (a < line->sizeline)
		{
			printf("%d %d %d %d %d\t", line->vector[a][0], line->vector[a][1], line->vector[a][2], line->vector[a][3], line->vector[a][4]);
			++a;
		}
		printf("\n");
		line = line->next;
	}

	line = ft_whichline(1);
	while (line->next)
		line = line->next;
	printf("%d\n", line->line);
	coo = (int***)malloc(sizeof(int**) * line->line);
	line = ft_whichline(1);
	while (line)
	{
		coo[line->line - 1] = (int**)malloc(sizeof(int*) * line->sizeline);
		a = 0;
		while (a < line->sizeline)
		{
			coo[line->line - 1][a] = line->vector[a];
			++a;
		}
		line = line->next;
	}
	line = ft_whichline(1);
	while (line)
	{
		a = 0;
		while (a < line->sizeline)
		{
			if (line->next && a < line->next->sizeline)
			{
				printf("xa = %d\n", coo[line->line - 1][a][2]);
				printf("ya = %d\n", coo[line->line - 1][a][3]);
				printf("xb = %d\n", coo[line->line][a][2]);
				printf("yb = %d\n\n", coo[line->line][a][3]);
			}
			if (a < line->sizeline - 1)
			{
				printf("xa = %d\n", coo[line->line - 1][a][2]);
				printf("ya = %d\n", coo[line->line - 1][a][3]);
				printf("xb = %d\n", coo[line->line - 1][a + 1][2]);
				printf("yb = %d\n\n", coo[line->line - 1][a + 1][3]);
			}
			++a;
		}
		line = line->next;
	}
	return (1);
}


t_line      *ft_convert(char *map)
{
	int     a;
	int     b;
	int     l;
	t_line  *tmp;

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
				while (map[a] != ' ' && map[a] != '\t' && map[a] != '\n'
						&& map[a])
					++a;
			else
				++a;
		}

		if (map[a] == '\n' || !map[a])
		{
			if (!(tmp->vector = (int**)malloc(sizeof(int*) * tmp->sizeline)))
				return (NULL);
			a = b;
			b = 0;
			while (map[a] && map[a] != '\n')
			{
				if (ft_isdigit(map[a]) ||
						(map[a] == '-' && ft_isdigit(map[a + 1])))
				{
					tmp->vector[b] = (int*)malloc(sizeof(int) * 6);

					tmp->vector[b][0] = 1;
					tmp->vector[b][1] = 3;
					tmp->vector[b][2] = b;
					tmp->vector[b][3] = l - 1;
					tmp->vector[b][4] = ft_atoifdf(&map[a]);
					while (map[a] != ' ' && map[a] != '\t' &&
							map[a] != ',' && map[a] != '\n' && map[a])
						++a;
					tmp->vector[b][5] = ((map[a] == ',' &&
								ft_isdigit(map[a + 1])) ?
							ft_atoifdf(&map[a + 1]) : 0xFFFFFF);
					while (map[a] != ' ' && map[a] != '\t' &&
							map[a] != '\n' && map[a])
						++a;
					++b;
				}
				else
					++a;
			}
			++l;
		}
		if (map[a])
			++a;
	}
	return (tmp);
}

int  main(int argc, char **argv)
{
	int     fd;
	int     a;
	char    buf[151];
	char    *map;
	char    *tmp;

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
	if (a == -1 || ((a = 1) && !(ft_test(ft_convert(map)))))
		ft_putstr("error read or display\n");
	return (0);
}
