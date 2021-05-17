#include "cub3D_bonus.h"

long int	create_trgb(unsigned long int t, unsigned long int r,
		unsigned long int g, unsigned long int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
