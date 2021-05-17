#include "cub3D.h"

int	main(int argc, char **arg)
{
	t_list	*lst;
	t_game	*game;
	int		fd;

	if (argc > 1 && ft_finder(arg[1], ".cub"))
	{
		fd = open(arg[1], O_RDONLY);
		if (fd != -1)
		{
			lst = ft_read_cub(fd);
			ft_format_cub(&lst);
			game = ft_parser_cub(lst);
			if (argc == 3 && !ft_strncmp("--save", arg[argc - 1], 6))
				game->save = 1;
			if (ft_verification_game(game))
				ft_my_mlx_loop(game);
			else
				ft_putstr_fd("invalid cub file or missing elements\n", 1);
			ft_free_game(game);
		}
		printf("Error:\nfile cub not found\n");
		close(fd);
	}
	return (0);
}
