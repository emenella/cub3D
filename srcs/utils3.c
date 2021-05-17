#include "cub3D.h"

t_wall	*ft_init_wall(void)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	if (!wall)
		return (NULL);
	wall->NO = NULL;
	wall->SO = NULL;
	wall->WE = NULL;
	wall->EA = NULL;
	return (wall);
}

t_player	*ft_init_player(char c, int y, int x)
{
	t_player	*player;
	size_t		i;

	i = -1;
	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->posX = x;
	player->posY = y;
	player->camera = ft_init_vector(0, 0);
	player->ray = ft_init_vector(0, 0);
	player->dir = ft_set_dir(c);
	player->plane = ft_create_vector_angle(player->dir, 90);
	return (player);
}

t_vector	*ft_set_dir(char c)
{
	int		i;
	char	arg[4];

	i = -1;
	arg[0] = 'N';
	arg[1] = 'S';
	arg[2] = 'W';
	arg[3] = 'E';
	while (++i < 4)
		if (c == arg[i])
			break ;
	if (i == 0)
		return (ft_init_vector(0, -1));
	else if (i == 1)
		return (ft_init_vector(0, 1));
	else if (i == 2)
		return (ft_init_vector(-1, 0));
	else if (i == 3)
		return (ft_init_vector(1, 0));
	return (NULL);
}

t_mlx	*ft_init_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = NULL;
	mlx->win = NULL;
	return (mlx);
}

t_vector	*ft_init_vector(double x, double y)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}
