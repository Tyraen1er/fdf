#include "mlx.h"
#include <stdio.h>
#include "libft.h"
#include <math.h>

void    ft_drawline(void *mlx, void *win, int xa, int xb, int ya, int yb)
{
	int     xav;
	int     yav;
	int     x;
	int     y;

	x = xa;
	y = ya;
	xav = (xa < xb) ? 1 : -1;
	yav = (ya < yb) ? 1 : -1;
	if (abs(xa - xb) < abs(ya - yb))
		while ((yav == 1 && y < yb) || (yav == -1 && y > yb))
		{
			if (!(abs(((xb - xa) * x) / (yb - ya))))
				x += xav;
			mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
			y += yav;
		}
	else
		while ((xav == 1 && x < xabyab[1]) || (xav == -1 && x > xabyab[1]))
		{
			if (abs(((xabyab[1] - xabyab[0]) * x) / (xabyab[3] - xabyab[2])))
				y += yav;
			mlx_pixel_put(mlx, win, x, y, color);
			x += xav;
		}
}

int		my_expose_fct(int exposecode, void *param)
{
	printf("expose_fct signale :\n%d\n", exposecode);
	param = NULL;
	return (0);
}

int		my_mouse_fct(int mousecode, void *param)
{
	printf("la souris dit :\n%d\n", mousecode);
	param = NULL;
	return (0);
}

int		my_key_fct(int keycode, void *param)
{
	if (keycode == 53)
	{
		printf("vous avez appuyer sur echap : bouton 53\nfermeture programme\n");
		exit(3);
	}
	printf("il se passe quelquechose\n%d\n", keycode);
	param = NULL;
	return (0);
}

int main()
{
	void	*mlx;
	void	*win;

// renvoie un void* qui sera un identifiant de connexion
	mlx = mlx_init();

// renvoie ID de la fenetre (ID, Size_t X, size_t y, nom fenetre)
	win = mlx_new_window(mlx, 1000, 1000, "mlx 42");

//(ID connexion, ID fenetre, pos X, pos Y, couleur en int 0x00 Rouge Bleu Vert)
	mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);

// traçage d une droite fait maison
	ft_drawline(mlx, win, 100, 200, 100, 200);

//(ID fenetre, pointeur sur fct, pointeur qui ne sera pas modifié)
	mlx_key_hook(win, my_key_fct, 0);

	printf("coco\n");
// idem souris pour clic gauche ou droit seulement
	mlx_mouse_hook(win, my_mouse_fct, 0);

// idem expose ?
	mlx_expose_hook(win, my_expose_fct, 0);

//Maintient la fenetre ouverte
	mlx_loop(mlx);

	return (0);
}
