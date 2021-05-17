#include "cub3D.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (data->width > x && data->height > y)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_my_mlx_unhook(int keycode, t_game *game)
{
	if (keycode == 0)
		game->player->input_front = 0;
	if (keycode == 2)
		game->player->input_front = 0;
	if (keycode == 1)
		game->player->input_side = 0;
	if (keycode == 13)
		game->player->input_side = 0;
	if (keycode == 123)
		game->player->input_rotate = 0;
	if (keycode == 124)
		game->player->input_rotate = 0;
	return (0);
}

int	ft_my_mlx_hook(int keycode, t_game *game)
{
	if (keycode == 0)
		game->player->input_front = 1;
	if (keycode == 2)
		game->player->input_front = -1;
	if (keycode == 1)
		game->player->input_side = 1;
	if (keycode == 13)
		game->player->input_side = -1;
	if (keycode == 123)
		game->player->input_rotate = 1;
	if (keycode == 124)
		game->player->input_rotate = -1;
	if (keycode == 53)
		ft_close(game);
	return (0);
}

void	ft_move(t_game *game)
{
	if (game->player->input_front == 1)
	{
		if (game->map->map[(int)(game->player->posY - (game->player->speed
					* game->player->dir->x))][(int)game->player->posX] != '1')
			game->player->posY -= (game->player->speed * game->player->dir->x);
		if (game->map->map[(int)game->player->posY][(int)(game->player->posX
			+ (game->player->speed * game->player->dir->y))] != '1')
			game->player->posX += (game->player->speed * game->player->dir->y);
	}
	if (game->player->input_front == -1)
	{
		if (game->map->map[(int)(game->player->posY + (game->player->speed
					* game->player->dir->x))][(int)game->player->posX] != '1')
			game->player->posY += (game->player->speed * game->player->dir->x);
		if (game->map->map[(int)game->player->posY][(int)(game->player->posX
			- (game->player->speed * game->player->dir->y))] != '1')
			game->player->posX -= (game->player->speed * game->player->dir->y);
	}
	ft_move1(game);
	if (game->player->input_rotate == 1)
		ft_rotate_player_right(game->player);
	if (game->player->input_rotate == -1)
		ft_rotate_player_left(game->player);
}

void	ft_move1(t_game *game)
{
	if (game->player->input_side == 1)
	{
		if (game->map->map[(int)(game->player->posY - (game->player->speed
					* game->player->dir->y))][(int)game->player->posX] != '1')
			game->player->posY -= (game->player->speed * game->player->dir->y);
		if (game->map->map[(int)game->player->posY][(int)(game->player->posX
			- (game->player->speed * game->player->dir->x))] != '1')
			game->player->posX -= (game->player->speed * game->player->dir->x);
	}
	if (game->player->input_side == -1)
	{
		if (game->map->map[(int)(game->player->posY + (game->player->speed
					* game->player->dir->y))][(int)game->player->posX] != '1')
			game->player->posY += (game->player->speed * game->player->dir->y);
		if (game->map->map[(int)game->player->posY][(int)(game->player->posX
			+ (game->player->speed * game->player->dir->x))] != '1')
			game->player->posX += (game->player->speed * game->player->dir->x);
	}
}
