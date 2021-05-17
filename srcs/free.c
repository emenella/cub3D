#include "cub3D.h"

void	ft_free_wall(t_wall *wall, t_mlx *mlx)
{
	size_t	i;

	t_texture (**texture[]) = {
	&(wall->NO), &(wall->SO), &(wall->WE), &(wall->EA)};
	i = -1;
	while (++i < sizeof(texture) / sizeof(*texture))
		if (*texture[i])
			ft_free_texture(*texture[i], mlx);
	free(wall);
}

void	ft_free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx);
}

void	ft_free_image(t_mlx *mlx, t_image *img)
{
	if (img->img)
	{
		mlx_destroy_image(mlx->mlx, img->img);
		img->img = NULL;
		img->addr = NULL;
	}
	free(img);
}

void	ft_free_texture(t_texture *texture, t_mlx *mlx)
{
	if (texture->img)
		ft_free_image(mlx, texture->img);
	if (texture->path)
	{
		free(texture->path);
		texture->path = NULL;
	}
	free(texture);
}

void	ft_free_map(t_map *map)
{
	ft_free_double_array(map->map, map->height);
	free(map);
}
