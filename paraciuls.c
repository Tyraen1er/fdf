#include "libft.h"
#include <stdio.h>

int		ft_color(int a)
{
	if (-125 < a && a < 128)
		return (8388607 + a * 65535);
	return ((a < 128) ? 0xFFFFFF : 196732);
}

int main()
{

}
