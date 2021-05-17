#include "cub3D.h"

void	ft_map_to_image(t_mlx *mlx, t_game *game)
{
	int	y;
	int	x;

	ft_init_minimap(game);
	y = -1;
	x = -1;
	while (++y < mlx->minimap->height)
	{
		while (++x < mlx->minimap->width)
		{
			if (y % mlx->minimap->heightsquare == 0
				|| x % mlx->minimap->widthsquare == 0)
				my_mlx_pixel_put(mlx->minimap, x, y, 0xFF0000);
			else if (game->map->map[y / mlx->minimap->heightsquare]
				[x / mlx->minimap->widthsquare] == '1')
				my_mlx_pixel_put(mlx->minimap, x, y, 0x00);
			else
				my_mlx_pixel_put(mlx->minimap, x, y, 0xFFFFFF);
		}
		x = -1;
	}
	ft_draw_player_on_minimap(game);
}

void	ft_fov(t_game *game, int w)
{
	int	x;

	x = -1;
	game->mlx->screen = ft_init_image(game->mlx->mlx,
			game->width, game->height);
	while (++x < w)
	{
		game->player->camera->x = (2 * x) / (double)w - 1;
		game->player->ray->x = game->player->dir->x + game->player->plane->x
			* game->player->camera->x;
		game->player->ray->y = game->player->dir->y + game->player->plane->y
			* game->player->camera->x;
		ft_ray(game, game->player->ray, x);
	}
}

void	ft_init_minimap(t_game *game)
{
	int	width;

	width = game->width - game->width * 80 / 100;
	game->mlx->minimap = ft_init_image(game->mlx->mlx, width, width);
	game->mlx->minimap->widthsquare = game->mlx->minimap->width
		/ game->map->width
		+ (game->mlx->minimap->width % game->map->width != 0);
	game->mlx->minimap->heightsquare = game->mlx->minimap->height
		/ game->map->height
		+ (game->mlx->minimap->height % game->map->height != 0);
}

void	ft_draw_player_on_minimap(t_game *game)
{
	ft_draw_square(game->mlx->minimap, 10, game->player->posY
		* game->mlx->minimap->heightsquare,
		game->player->posX * game->mlx->minimap->widthsquare);
}

void	ft_draw_square(t_image *data, int size, int center_y, int center_x)
{
	int	y;
	int	x;

	y = center_y - (size / 2);
	x = center_x - (size / 2);
	while (y < center_y + (size / 2))
	{
		while (x < center_x + (size / 2))
		{
			my_mlx_pixel_put(data, x, y, 0x0000FF);
			x++;
		}
		x = center_x - (size / 2);
		y++;
	}
}
