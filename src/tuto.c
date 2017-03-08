#include "mlx.h"
#include <stdio.h>
#include "libft.h"

int my_key_fct(int keycode, void *param)
{
	if (keycode == 53)
		exit(3);
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
	win = mlx_new_window(mlx, 400, 400, "mlx 42");


//(ID connexion, ID fenetre, pos X, pos Y, couleur en int 0x00 Rouge Bleu Vert)
	mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);

//(ID fenetre, pointeur sur fct, pointeur qui ne sera pas modifié)
mlx_key_hook(win, my_key_fct, 0);

//Maintient la fenetre ouverte
	mlx_loop(mlx);

	return (0);
}
