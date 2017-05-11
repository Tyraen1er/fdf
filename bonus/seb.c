#include "libft.h"
#include <fcntl.h>

void writing(void *mlx, void *win, int **coo, int nombre)
{
	int		xabyab[5];
	int		**aff;
	int		a;
	int		b;

	a = 0;
	xabyab[4] = 0xFFFFFF;
	while (a < nombre)
	{
		aff[a] = ft_param(coo[a]);
		++a;
	}
	a = 0;
	while (a < nombre)
	{
		xabyab[0] = aff[a][2];
		xabyab[2] = aff[a][3];
		++a;
		xabyab[1] = aff[a][2];
		xabyab[3] = aff[a][3];
		++a;
		ft_drawline(mlx, win, xabyab);
	}
}

void ft_display()
{
	ft_putstr("tout semble fonctionner\n");
}

void	ft_parsing(char *file)
{
	char	*tmp;
	int		**coo;
	int		a;
	int		b;
	int		nombre;

	nombre = 0;
	tmp = file;
	while (*file)
	{
		if (ft_isdigit(*file) && ++nombre)
			while (ft_isdigit(*file) && *file)
				++file;
		++file;
	}
	if (nombre % 3 || nombre % 2)
	{
		ft_putstr("mauvais : il manque des coordonnees\n");
		return ;
	}
	coo = (int**)malloc(sizeof(int*) * a / 3);
	file = tmp;
	a = 0;
	while (*file)
	{
		b = 0;
		if (ft_isdigit(*file))
		{
			coo[a] = malloc(sizeof(int) * 3);
			while (b != 2 && *file)
			{
				if (ft_isdigit(*file) && ++b)
					coo[a][b] = ft_atoi(file);
				++file;
			}
		}
		++file;
	}
	ft_display(coo, nombre);
}

int main(int ac, char **av)
{
	char	*file;
	char	*tmp;
	char	buf[151];
	int		a;
	int		b;

	if (ac != 2)
	{
		ft_putstr("usage: ./fdf fichier_map\n");
		return (0);
	}
	a = open(av[1], O_RDONLY);
	buf[150] = 0;
	file = ft_memalloc(1);
	while (0 < (b = read(a, buf, 150)))
	{
		tmp = file;
		file = ft_strjoin(file, buf);
		free(tmp);
	}
	if (b == -1 || a == -1 || !file)
		ft_putstr("error reading\n");
	ft_parsing(file);
	return (0);
}
