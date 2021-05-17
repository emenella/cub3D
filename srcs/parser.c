#include "cub3D.h"

int	ft_argchr(t_list *cub)
{
	size_t	i;
	char	*arg[8];

	arg[0] = "R";
	arg[1] = "NO";
	arg[2] = "SO";
	arg[3] = "WE";
	arg[4] = "EA";
	arg[5] = "S";
	arg[6] = "F";
	arg[7] = "C";
	i = -1;
	while (++i < sizeof(arg) / sizeof(*arg))
	{
		if (ft_finder(cub->content, arg[i]))
		{
			if (i == 0)
				return (0);
			if (i > 0 && i < 6)
				return (1);
			if (i > 5)
				return (2);
		}
	}
	return (-1);
}

void	ft_parser_resolution(t_list *cub, t_game *game)
{
	size_t	i;
	char	*str;

	i = -1;
	str = ft_strdup("");
	while (!ft_isdigit(cub->content[++i]))
		;
	while (ft_isdigit(cub->content[i]))
	{
		ft_add_c(-1, &str, cub->content[i], ft_strlen(str));
		i++;
	}
	game->width = ft_atoi(str);
	free(str);
	str = NULL;
	str = ft_strdup("");
	while (ft_isdigit(cub->content[++i]))
		ft_add_c(-1, &str, cub->content[i], ft_strlen(str));
	game->height = ft_atoi(str);
	free (str);
	str = NULL;
}

void	ft_parser_texture(t_list *cub, t_game *game)
{
	size_t	i;
	char	*arg[5];

	arg[0] = "NO";
	arg[1] = "SO";
	arg[2] = "WE";
	arg[3] = "EA";
	arg[4] = "S";
	t_texture (**texture[]) = {
	&(game->wall->NO),
	&(game->wall->SO),
	&(game->wall->WE),
	&(game->wall->EA),
	&(game->sprite)};
	i = -1;
	while (++i < sizeof(arg) / sizeof(*arg))
	{
		if (ft_finder(cub->content, arg[i]))
		{
			*texture[i] = ft_init_texture(
					ft_strdup(ft_strchr(cub->content, '.')));
			return ;
		}
	}
}

void	ft_parser_color(t_list *cub, t_game *game)
{
	char	**data;
	char	*args;
	size_t	i;

	t_RGB (**element[]) = {
	&(game->floor),
	&(game->ceiling)};
	args = ft_strdup("FC");
	i = -1;
	while (++i < 2)
	{
		if (ft_strncmp(&args[i], cub->content, 1) == 0)
		{
			data = ft_split(&cub->content[2], ',');
			*element[i] = ft_init_RGB(ft_atoi(data[0]),
					ft_atoi(data[1]), ft_atoi(data[2]), 0);
			ft_free_double_array(data, 3);
		}
	}
	free(args);
}

void	ft_parser_map(t_list **cub, t_game *game)
{
	int		width;
	int		height;
	char	**result;
	t_list	*lst;
	int		i;

	lst = *cub;
	i = -1;
	width = ft_max_line(cub);
	height = ft_lstsize(lst);
	result = malloc(sizeof(char *) * height);
	if (!result)
		ft_exit(MALLOC_ERROR, game);
	while (lst != NULL && ++i < height)
	{
		result[i] = malloc(sizeof(char) * (width + 1));
		if (!result[i])
			ft_exit(MALLOC_ERROR, game);
		ft_memset(result[i], ' ', width + 1);
		ft_strlcpy(result[i], lst->content, width + 1);
		ft_listfree(lst, cub);
		lst = *cub;
	}
	game->map = ft_init_map(result, height, width);
}
