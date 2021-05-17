#include "cub3D_bonus.h"

void	ft_mlx_init_texture(t_game *game)
{
	size_t	i;

	char (*texture[]) = {
		game->wall->NO->path,
		game->wall->SO->path,
		game->wall->WE->path,
		game->wall->EA->path,
		game->sprite->path};
	t_image (**img[]) = {
	&game->wall->NO->img,
	&game->wall->SO->img,
	&game->wall->WE->img,
	&game->wall->EA->img,
	&game->sprite->img};
	i = -1;
	while (++i < sizeof(texture) / sizeof(*texture))
	{
		(*img[i]) = malloc(sizeof(t_image));
		if (!(*img[i]))
			ft_exit(MALLOC_ERROR, game);
		(*img[i])->img = mlx_xpm_file_to_image(game->mlx->mlx, texture[i],
				&(*img[i])->width, &(*img[i])->height);
		if ((*img[i])->img == 0)
			ft_exit("Texture incorrect", game);
	}
}

void	ft_mlx_get_address_texture(t_game *game)
{
	size_t	i;

	t_image (**img[]) = {
	&game->wall->NO->img,
	&game->wall->SO->img,
	&game->wall->WE->img,
	&game->wall->EA->img,
	&game->sprite->img};
	i = -1;
	while (++i < sizeof(img) / sizeof(*img))
	{
		(*img[i])->addr = mlx_get_data_addr((*img[i])->img,
				&(*img[i])->bits_per_pixel,
				&(*img[i])->line_length,
				&(*img[i])->endian);
		if ((*img[i])->addr == 0)
			ft_exit("Texture incorrect", game);
	}
}
