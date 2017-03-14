int		my_key_fct(int keycode, void *pdf)
{
	if (keycode == 53)
		exit(3);
	printf("il se passe quelquechose\n%d\n", keycode);
	if (keycode == 123)
		pdf[0] -= 10;
	if (keycode == 124)
		pdf[0] += 10;
	if (keycode == 125)
		pdf[1] -= 10;
	if (keycode == 126)
		pdf[1] += 10;
	return (0);
}

void    ft_drawline(void *mlx, void *win, int *xabyab)
{
	int     xav;
	int     yav;
	int     x;
	int     y;

	x = xabyab[0];
	y = xabyab[2];
	xav = (xabyab[0] < xabyab[1]) ? 1 : -1;
	yav = (xabyab[2] < xabyab[3]) ? 1 : -1;
	if (xabyab[0] == xabyab[1])
		while (y != xabyab[3])
		{
			mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
			y += yav;
		}
	else
		while ((xav == 1 && x < xabyab[1]) || (xav == -1 && x > xabyab[1]))
		{
			if (abs(((xabyab[1] - xabyab[0]) * x) / (xabyab[3] - xabyab[2])))
				y += yav;
			mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
			x += xav;
		}
}
