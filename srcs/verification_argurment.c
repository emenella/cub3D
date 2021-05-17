#include "cub3D.h"

int	ft_isspace_touch(t_map *map, int i, int j)
{
	if (map->map[i][j] == 0)
		return (0);
	if (i == map->height - 1 || j == map->width - 1 || i == 0 || j == 0)
		return (1);
	if (map->map[i + 1][j] != 32 && map->map[i - 1][j]
		!= 32 && map->map[i][j + 1] != 32 && map->map[i][j - 1] != 32)
		return (0);
	return (1);
}

int	ft_verification_map(t_map *map)
{
	int		i;
	int		j;
	char	*block;

	i = -1;
	j = -1;
	block = ft_strdup(BLOCK);
	while (++i < map->height)
	{
		while (++j < map->width)
		{
			if (ft_strchr(&block[1], map->map[i][j])
					&& ft_isspace_touch(map, i, j))
			{
				free(block);
				block = NULL;
				return (0);
			}
		}
		j = -1;
	}
	free(block);
	block = NULL;
	return (1);
}

int	ft_verification_game(t_game *game)
{
	if (!game->player)
		ft_exit("invalid player or missing", game);
	if (!game->wall->SO)
		ft_exit("missing texture South", game);
	if (!game->wall->NO)
		ft_exit("missing texture North", game);
	if (!game->wall->WE)
		ft_exit("missing texture West", game);
	if (!game->wall->EA)
		ft_exit("missing texture East", game);
	if (!game->ceiling)
		ft_exit("missing color ceiling", game);
	if (!game->floor)
		ft_exit("missing color floor", game);
	if (!ft_verification_map(game->map))
		ft_exit("invalid map", game);
	return (1);
}
