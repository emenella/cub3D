#include "cub3D_bonus.h"

void	ft_ray(t_game *game, t_vector *vector, int pixel)
{
	float		walldist;
	int			side;
	float		wallx;
	t_sprites	*sprites;
	t_draw		draw;

	sprites = NULL;
	side = ft_get_distance(game, vector, &sprites, &walldist);
	draw.x = pixel;
	draw.lineHeight = (int)(game->mlx->screen->height / walldist);
	draw.drawStart = -draw.lineHeight / 2 + game->mlx->screen->height / 2;
	if (draw.drawStart < 0)
		draw.drawStart = 0;
	draw.drawEnd = draw.lineHeight / 2 + game->mlx->screen->height / 2;
	if (draw.drawStart >= game->mlx->screen->height)
		draw.drawEnd = game->mlx->screen->height - 1;
	wallx = 0;
	if (side == 0)
		wallx = game->player->posY + walldist * vector->y;
	else
		wallx = game->player->posX + walldist * vector->x;
	wallx -= floor(wallx);
	ft_draw_wall_texture(game, side, wallx, &draw);
	ft_sprite(&sprites, game, pixel);
}

void	ft_draw_wall_texture(t_game *game, int side, double wallx, t_draw *draw)
{
	int				textX;
	int				i;
	unsigned int	color;
	int				textY;
	t_image			*texture;

	texture = ft_select_texture(game, &textX, wallx, side);
	i = draw->drawStart - 1;
	while (++i < draw->drawEnd)
	{
		textY = (i * 2 - game->mlx->screen->height + draw->lineHeight)
			* (texture->height / 2) / draw->lineHeight;
		color = *(unsigned int *)(texture->addr + (textY * texture->line_length
					+ textX * (texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(game->mlx->screen, draw->x, i, color);
	}
	ft_draw_ceilling_floor(game, draw);
}

void	ft_sprite(t_sprites **sprites, t_game *game, int x)
{
	t_sprites	*lst;
	t_sprite	s;
	int			d;

	lst = *sprites;
	while (lst != NULL)
	{
		ft_calcul_sprite(&s, game, lst);
		if (s.drawStartX <= x && x < s.drawEndX)
			ft_draw_sprite(&s, &d, game, x);
		lst = lst->next;
	}
	ft_spritesfree(*sprites);
}

void	ft_draw_sprite(t_sprite *s, int *d, t_game *game, int x)
{
	s->textX = (int)(256 * (x - (-s->spriteWidth / 2 + s->spriteScreenX))
			* game->sprite->img->width / s->spriteWidth) / 256;
	s->y = s->drawStartY;
	while (s->y < s->drawEndY)
	{
		*d = (s->y * 256 - game->mlx->screen->height * 128
				+ s->spriteHeight * 128);
		s->textY = ((*d * game->sprite->img->height)
				/ s->spriteHeight) / 256;
		s->color = *(unsigned int *)(game->sprite->img->addr + (s->textY
					* game->sprite->img->line_length + s->textX
					* (game->sprite->img->bits_per_pixel / 8)));
		if ((s->color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(game->mlx->screen, x, s->y, s->color);
		s->y++;
	}
}

int	rendu(t_game *game)
{
	ft_move(game);
	ft_map_to_image(game->mlx, game);
	ft_fov(game, game->width);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->screen->img, 0, 0);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win,
		game->mlx->minimap->img, game->mlx->screen->width
		- game->mlx->minimap->width, game->mlx->screen->height
		- game->mlx->minimap->height);
	if (game->save)
	{
		ft_save(game->mlx->screen);
		game->save = 0;
	}
	ft_free_image(game->mlx, game->mlx->screen);
	ft_free_image(game->mlx, game->mlx->minimap);
	ft_fps(game);
	return (0);
}
