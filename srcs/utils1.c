#include "cub3D.h"

t_image	*ft_init_image(void *mlx, int width, int height)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->img = mlx_new_image(mlx, width, height);
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	image->width = width;
	image->height = height;
	return (image);
}

int	ft_finder(char *src, char *find)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = ft_strlen(find);
	while (src[++i] && find[j])
	{
		if (src[i] == find[j])
			j++;
		else
			j = 0;
		if (j == len)
			return (1);
	}
	return (0);
}

void	ft_add_c(int i, char **str, char c, int len)
{
	char	*result;

	result = NULL;
	if (i > 0)
	{
		result = malloc(sizeof(char) * len + i + 1);
		if (!result)
			return ;
		ft_memset(result, c, i);
		ft_memcpy(result + i, *str, len);
		result[len + i] = '\0';
	}
	else if (i < 0)
	{
		result = malloc(sizeof(char) * len + (-i) + 1);
		if (!result)
			return ;
		ft_memcpy(result, *str, len);
		ft_memset(result + len, c, (-i));
		result[len + (-i)] = '\0';
	}
	free(*str);
	*str = result;
	str = NULL;
}

void	ft_draw_ceilling_floor(t_game *game, t_draw *draw)
{
	t_draw	ceiling;
	t_draw	floor;

	ceiling.drawStart = 0;
	ceiling.drawEnd = draw->drawStart;
	ceiling.x = draw->x;
	floor.drawStart = draw->drawEnd;
	floor.drawEnd = game->mlx->screen->height;
	floor.x = draw->x;
	ft_draw_line_verticale(game->mlx->screen, &ceiling,
		create_trgb(game->ceiling->t, game->ceiling->r,
			game->ceiling->g, game->ceiling->b));
	ft_draw_line_verticale(game->mlx->screen, &floor,
		create_trgb(game->floor->t, game->floor->r,
			game->floor->g, game->floor->b));
}

void	ft_free_double_array(char **str, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		free(str[i]);
	free(str);
	str = NULL;
}
