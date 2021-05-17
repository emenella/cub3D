#include "cub3D_bonus.h"

void	ft_listfree(t_list *lst, t_list **alst)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp && tmp != lst)
	{
		if (tmp->next == lst)
			tmp->next = lst->next;
		tmp = tmp->next;
	}
	if (lst == *alst)
		*alst = lst->next;
	if (alst)
	{
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = NULL;
	}
}

t_game	*ft_init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
		exit(-1);
	game->width = 0;
	game->height = 0;
	game->wall = NULL;
	game->sprite = NULL;
	game->floor = NULL;
	game->ceiling = NULL;
	game->map = NULL;
	game->player = NULL;
	game->mlx = NULL;
	game->save = 0;
	return (game);
}

t_texture	*ft_init_texture(char *path)
{
	t_texture	*texture;

	texture = NULL;
	texture = malloc(sizeof(t_texture));
	if (texture == NULL)
		return (NULL);
	texture->path = path;
	texture->img = NULL;
	return (texture);
}

t_RGB	*ft_init_RGB(int r, int g, int b, int t)
{
	t_RGB	*color;

	color = malloc(sizeof(t_RGB));
	if (color == NULL)
		return (NULL);
	if (r < 256 && g < 256 && g < 256 && t < 256)
	{
		color->r = r;
		color->g = g;
		color->b = b;
		color->t = t;
		return (color);
	}
	return (NULL);
}

void	ft_exit(char *str, t_game *game)
{
	ft_putstr_fd("Error:\n", 1);
	ft_putstr_fd(str, 1);
	ft_free_game(game);
	exit(-1);
}
