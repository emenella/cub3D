#include "cub3D_bonus.h"

t_vector	*ft_create_vector_angle(t_vector *v, double angle)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	angle = ft_degres_to_radian(angle);
	if (!vector)
		return (NULL);
	vector->x = cos(atan2(v->y, v->x) + angle);
	vector->y = sin(atan2(v->y, v->x) + angle);
	return (vector);
}

double	ft_degres_to_radian(double degres)
{
	return (degres * M_PI / 180);
}

void	ft_rotate_player_right(t_player *p)
{
	double	oldirX;
	double	oldplaneX;

	oldirX = p->dir->x;
	oldplaneX = p->plane->x;
	p->dir->x = p->dir->x * cos(-p->rot) - p->dir->y * sin(-p->rot);
	p->dir->y = oldirX * sin(-p->rot) + p->dir->y * cos(-p->rot);
	p->plane->x = p->plane->x * cos(-p->rot) - p->plane->y * sin(-p->rot);
	p->plane->y = oldplaneX * sin(-p->rot) + p->plane->y * cos(-p->rot);
}

void	ft_rotate_player_left(t_player *p)
{
	double	oldirX;
	double	oldplaneX;

	oldirX = p->dir->x;
	oldplaneX = p->plane->x;
	p->dir->x = p->dir->x * cos(p->rot) - p->dir->y * sin(p->rot);
	p->dir->y = oldirX * sin(p->rot) + p->dir->y * cos(p->rot);
	p->plane->x = p->plane->x * cos(p->rot) - p->plane->y * sin(p->rot);
	p->plane->y = oldplaneX * sin(p->rot) + p->plane->y * cos(p->rot);
}

void	ft_draw_line_verticale(t_image *data, t_draw *draw, unsigned int color)
{
	while (draw->drawStart < draw->drawEnd)
	{
		my_mlx_pixel_put(data, draw->x, draw->drawStart, color);
		draw->drawStart++;
	}
}
