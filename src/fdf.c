#include "mlx.h"
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>

// mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
/*
int		coefd(int xa, int ya, int xb, yb)
{
	(xb - xa) / (yb - ya)
}
*/
int		*ft_convert(char *map, int a)
{
	int		*coo;
	char	*tmp;

	tmp = map;
	while (*map)
	{
		if (*map == '\t' || *map == ' ' || *map == '\n')
			--a;
		++map;
	}
// Salut Manu, cest la que tu  tes arreté, et bah ça marche pas ! Bon courage !
	coo = (int[a]){0};
/*
	while (*map && (x = -1))
	{
		while (*map == ' ' || *map == '\t')
			++map;
		if (*map && *map != '+' && *map != '-' && !(ft_isdigit))
			return (-1);
	}
*/
	return (0);
}

int		ft_draw(int *coo)
{
	return (0);
}

int		ft_display(int *coo)
{
	void	*mlx;
	void	*win;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, 2000, 2000, "mlx 42");
//	mlx_key_hook(win, my_key_fct, 0);
	if (-1 == (ft_draw(int *coord)))
	mlx_loop(mlx);
}

int		my_key_fct(int keycode, void *param)
{
	if (keycode == 53)
		exit(3);
	printf("il se passe quelquechose\n%d\n", keycode);
	param = NULL;
	return (0);
}

int main(int argc, char **argv)
{
	int		fd;
	int		a;
	char	buf[151];
	char	*map;
	char	*tmp;

	*map = 0;
	if (!(map = NULL) && argc != 2)
	{
		ft_putstr("Le programme a besoin d'un seul fichier pour etre fonctionnel.\n");
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
	if (a == -1 || !(ft_display(ft_convert(map, a))))
		return (0);
	return (0);
}
