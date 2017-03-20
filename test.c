#include "libft.h"

int		*save_vector(int pos, int linemax, int z)
{
	int		*vector;

	vector = (int*)malloc(sizeof(int) * 5);
	vector[0] = 1;
	vector[1] = 3;
	vector[3] = pos / linemax;
	vector[2] = pos - (vector[2] * linemax);
	vector[4] = z;
	return (vector);
}

int		**ft_convert(char *map, int *a)
{
	int		b;
	int		**coo;
	char	*tmp;

	tmp = map - 1;
	while (*++tmp)
		if (*tmp == '\t' || *tmp == ' ' || (*tmp == '\n' && ++a[1]))
			++a[0];
	coo = (int**)malloc(sizeof(int*) * a[0]);
	b = 0;
	while (*map)
	{
		if (*map == ' ' || *map == '\t' || *map == '\n')
			++map;
		if (*map != ' ' && *map != '\t' && *map != '\n' &&
				*map != '+' && *map != '-' && !ft_isdigit(*map))
			return (NULL);
		if (*map)
			coo[b] = save_vector(b++, a[0] / a[1], ft_atoi(map));
		map = (*map == '+' || *map == '-') ? map + 1 : map;
		while (ft_isdigit(*map))
			++map;
	}
	return (coo);
}

int main()
{
	char	*map;
	int		a[2];
	int		**coo;

	a[0] = 0;
	a[1] = 0;
	map = (char*)malloc(10);
	map[0] = '5';
	map[1] = '6';
	map[2] = '1';
	map[3] = '2';
	map[4] = '5';
	map[5] = '9';
	map[6] = '8';
	map[7] = '7';
	map[8] = '0';
	map[9] = 0;
	coo = ft_convert(map, a);
}
