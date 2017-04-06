#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int		*matrice_multi(int *fst, double *scd)
{
	int	*ret;
	int	*tmp;
	int	x;
	int	y;
	int	a;

	y = -1;
	if (fst[0] != (int)scd[1])
	{
		printf("c est la merde chef !!!\n");
		return (NULL);
	}
	ret = (int*)ft_memalloc(sizeof(int) * ((int)(fst[1] * scd[0] + 2)));
	ret[0] = scd[0];
	ret[1] = fst[1];
	tmp = &ret[2];
	while (++y < fst[1] && (x = -1))
		while (++x < scd[0] && (a = -1))
			while (++a < fst[0])
				ret[(int)(2 + x + y * scd[0])] +=
					fst[a + y * fst[0] + 2] * scd[(int)(a * scd[0] + x + 2)];
	return (ret);
}

void		writing(int **coo, int *a)
{
	int		b;
	int		c;
	int		d;
	int		xabyab[4];

	b = -1;
	c = 0;
	d = a[0] / a[1] - 1;
	while (++b < a[0])
	{
		printf("au cas ou %d\n", b);
		if ((b + 1) % d || b < d)
		{
			xabyab[0] = coo[b][0];
			xabyab[2] = coo[b][1];
			xabyab[1] = coo[b + 1][0];
			xabyab[3] = coo[b + 1][1];
			printf("%d\n", b);
		}
	}               
}

int		*save_vector(int pos, int sizeline, int z)
{
	int		*vector;

	vector = (int*)malloc(sizeof(int) * 5);
	vector[0] = 1;
	vector[1] = 3;
	vector[3] = pos / sizeline;
	vector[2] = pos - (vector[3] * sizeline);
	vector[4] = z;
	return (vector);
}

int     **ft_convert(char *map, int *a)
{
	int		c;
	int		b;
	int		**coo;

	b = 0;
	c = 0;
	while(map[c] != '\n' && map[c])
		++c;
	printf("%d\n", c);
	while (map[b])
	{
		while (map[b] == ' ' || map[b] == '\t' ||
				(map[b] == '\n' && ++a[1]))
		{
			if (map[b] == '\n')
				printf("map = %d\n", b);
			++b;
		}
		if (map[b] == '+' || map[b] == '-')
			++b;
		if ((ft_isdigit(map[b]) && ++a[0]) || !map[b])
			while (ft_isdigit(map[b]))
				++b;
		else
		{
			printf("quit : map - map = %d\n", b);
			return (NULL);
		}
	}
	coo = (int**)malloc(sizeof(int*) * a[0]);
	b = 0;
	while (*map)
	{
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		coo[b] = save_vector(b, a[0] / a[1], ft_atoi(map));
		++b;
		while (ft_isdigit(*map) || *map == '+' || *map == '-')
			++map;
	}
	a[0]--;
	return(coo);
}
/*
int		**ft_convert(char *map, int *a)
{
	int		c;
	int		b;
	int		**coo;
	char	*tmp;

	tmp = map;
	while (*tmp)
	{
		while (*tmp == ' ' || *tmp == '\t' || (*tmp == '\n' && ++a[1]))
			++tmp;
		if (*tmp == '+' || *tmp == '-')
			++tmp;
		if ((ft_isdigit(*tmp) && ++a[0]) || !*tmp)
			while (ft_isdigit(*tmp))
				++tmp;
		else
			return (NULL);
	}
	coo = (int**)malloc(sizeof(int*) * a[0]);
	b = 0;
	c = 0;
	while (*map)
	{
		while (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		coo[b] = save_vector(b, a[0] / a[1], ft_atoi(map));
		++b;
		while (ft_isdigit(*map) || *map == '+' || *map == '-')
			++map;
	}
	return(coo);
}
*/
int main(int argc, char **argv)
{
	int		b;
	int		c;
	int     fd;
	int     a[2];
	int		**coo;
	char    buf[151];
	char    *map;
	char    *tmp;

	map = ft_memalloc(1);
	if (!(a[1] = 0) && argc != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while ((a[0] = read(fd, buf, 150)) && a[0] != -1)
	{
		buf[a[0]] = 0;
		tmp = ft_strjoin(map, buf);
		ft_memdel((void *)&map);
		map = tmp;
	}
//	writing(ft_convert(map, a), a);
	coo = ft_convert(map, a);
	if (!coo)
	{
		printf("NULL\n");
		return(0);
	}
	b = -1;
	printf("a[0] = %d\n", a[0]);
	while (++b < a[0])
	{
		printf("b = %d\n", b);
		c = -1;
		while (++c < coo[b][0] * coo[b][1] + 2)
			printf("coo[%d][%d] = %d\n", b, c, coo[b][c]);
	}
	return (0);
}
