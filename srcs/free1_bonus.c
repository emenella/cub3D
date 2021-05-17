#include "cub3D_bonus.h"

void	ft_free_player(t_player *player)
{
	free(player->dir);
	player->dir = NULL;
	free(player->plane);
	player->plane = NULL;
	free(player->camera);
	player->camera = NULL;
	free(player->ray);
	player->ray = NULL;
	free(player);
}

void	ft_free_game(t_game *game)
{
	if (game->wall)
		ft_free_wall(game->wall, game->mlx);
	if (game->sprite)
		ft_free_texture(game->sprite, game->mlx);
	if (game->map)
		ft_free_map(game->map);
	if (game->player)
		ft_free_player(game->player);
	if (game->floor)
	{
		free(game->floor);
		game->floor = NULL;
	}
	if (game->ceiling)
	{
		free(game->ceiling);
		game->ceiling = NULL;
	}
	if (game->mlx)
		ft_free_mlx(game->mlx);
	free(game);
}
