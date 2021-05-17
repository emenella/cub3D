#include "cub3D_bonus.h"

void	ft_fps(t_game *game)
{
	static double	oldtime = 0;
	static double	times = 0;
	char			*fps;

	oldtime = times;
	times = (double)clock();
	fps = ft_itoa(1.0 / ((times - oldtime) / CLOCKS_PER_SEC));
	mlx_string_put(game->mlx->mlx, game->mlx->win, game->width - 100,
		20, 0xFF0000, fps);
	free(fps);
	game->player->speed = (((times - oldtime) / CLOCKS_PER_SEC)) * 3;
	game->player->rot = (((times - oldtime) / CLOCKS_PER_SEC)) * 3;
}

int	ft_close(t_game *game)
{
	ft_free_game(game);
	exit (0);
	return (0);
}

void	ft_my_mlx_loop(t_game *game)
{
	game->mlx = ft_init_mlx();
	game->mlx->mlx = mlx_init();
	game->mlx->win = mlx_new_window(game->mlx->mlx, game->width,
			game->height, "cub3D");
	ft_mlx_init_texture(game);
	ft_mlx_get_address_texture(game);
	mlx_hook(game->mlx->win, 2, (1L << 0), &ft_my_mlx_hook, game);
	mlx_hook(game->mlx->win, 3, (1L << 1), &ft_my_mlx_unhook, game);
	mlx_hook(game->mlx->win, 17, 0, &ft_close, game);
	mlx_loop_hook(game->mlx->mlx, &rendu, game);
	mlx_loop(game->mlx->mlx);
}

t_image	*ft_select_texture(t_game *game, int *textX, double wallx, int side)
{
	if (side == 0 && game->player->ray->x > 0)
	{
		*textX = (int)(wallx * (double)game->wall->EA->img->width);
		return (game->wall->EA->img);
	}
	else if (side == 1 && game->player->ray->y < 0)
	{
		*textX = (int)(wallx * (double)game->wall->NO->img->width);
		return (game->wall->NO->img);
	}
	else if (side == 0 && game->player->ray->x < 0)
	{
		*textX = (int)(wallx * (double)game->wall->WE->img->width);
		*textX = game->wall->WE->img->width - *textX - 1;
		return (game->wall->WE->img);
	}
	else
	{
		*textX = (int)(wallx * (double)game->wall->SO->img->width);
		*textX = game->wall->SO->img->width - *textX - 1;
		return (game->wall->SO->img);
	}
}

void	ft_dda(t_dda *dda, t_game *game, t_sprites **sprites)
{
	while (game->map->map[dda->y][dda->x] != '1')
	{
		if (dda->sidedistX < dda->sidedistY)
		{
			dda->sidedistX += dda->deltaX;
			dda->x += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sidedistY += dda->deltaY;
			dda->y += dda->stepY;
			dda->side = 1;
		}
		if (game->map->map[dda->y][dda->x] == '2')
			ft_spritesadd_front(sprites, ft_spritesnew(dda->x, dda->y));
	}
}
