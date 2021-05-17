#include "cub3D.h"

void	ft_parser_player_spawn(t_game *game)
{
	int		y;
	int		x;
	char	*arg;
	char	*dir;

	x = -1;
	y = -1;
	arg = ft_strdup("NSWE");
	game->player = NULL;
	while (++y < game->map->height)
	{
		while (++x < game->map->width)
		{
			dir = ft_strchr(arg, game->map->map[y][x]);
			if (dir && !game->player && dir[0] != 0)
			{
				game->player = ft_init_player(dir[0], y, x);
				free(arg);
				return ;
			}
		}
		x = -1;
	}
	free(arg);
	ft_exit("No spawn set", game);
}

t_game	*ft_parser_cub(t_list *cub)
{
	t_game			*game;
	int				typearg;
	void			(*parser[3])(t_list*, t_game*);

	parser[0] = &ft_parser_resolution;
	parser[1] = &ft_parser_texture;
	parser[2] = &ft_parser_color;
	game = ft_init_game();
	game->wall = ft_init_wall();
	while (cub)
	{
		typearg = ft_argchr(cub);
		if (typearg > -1 && typearg < (int)(sizeof(parser) / sizeof(*parser)))
		{
			parser[typearg](cub, game);
			ft_listfree(cub, &cub);
		}
		else
			ft_parser_map(&cub, game);
	}
	if (game->map)
		ft_parser_player_spawn(game);
	return (game);
}
