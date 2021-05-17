#include "cub3D.h"

void	ft_calcul_sprite(t_sprite *s, t_game *game, t_sprites *lst)
{
	s->spriteX = lst->x + 0.5 - game->player->posX;
	s->spriteY = lst->y + 0.5 - game->player->posY;
	s->invdet = 1.0 / (game->player->plane->x * game->player->dir->y
			- game->player->dir->x * game->player->plane->y);
	s->transformX = s->invdet * (game->player->dir->y * s->spriteX
			- game->player->dir->x * s->spriteY);
	s->transformY = s->invdet * (-game->player->plane->y * s->spriteX
			+ game->player->plane->x * s->spriteY);
	s->spriteScreenX = (int)game->mlx->screen->width / 2
		* (1 + s->transformX / s->transformY);
	s->spriteHeight = abs((int)(game->mlx->screen->height / (s->transformY)));
	s->drawStartY = -s->spriteHeight / 2 + game->mlx->screen->height / 2;
	if (s->drawStartY < 0)
		s->drawStartY = 0;
	s->drawEndY = s->spriteHeight / 2 + game->mlx->screen->height / 2;
	if (s->drawEndY >= game->mlx->screen->height)
		s->drawEndY = game->mlx->screen->height;
	s->spriteWidth = abs((int)(game->mlx->screen->height / (s->transformY)));
	s->drawStartX = -s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawStartX < 0)
		s->drawStartX = 0;
	s->drawEndX = s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawEndX >= game->mlx->screen->width)
		s->drawEndX = game->mlx->screen->width;
}

int	ft_get_distance(t_game *game, t_vector *vector,
		t_sprites **sprites, float *walldist)
{
	t_dda	dda;

	if (vector->y == 0)
		dda.deltaX = 0;
	else if (vector->x == 0)
		dda.deltaX = 1;
	else
		dda.deltaX = fabs(1 / vector->x);
	if (vector->x == 0)
		dda.deltaY = 0;
	else if (vector->y == 0)
		dda.deltaY = 1;
	else
		dda.deltaY = fabs(1 / vector->y);
	dda.x = game->player->posX;
	dda.y = game->player->posY;
	ft_init_step(&dda, game, vector);
	ft_dda(&dda, game, sprites);
	if (dda.side == 0)
		*walldist = (dda.x - game->player->posX
				+ (1 - dda.stepX) / 2) / vector->x;
	else
		*walldist = (dda.y - game->player->posY
				+ (1 - dda.stepY) / 2) / vector->y;
	return (dda.side);
}

void	ft_init_step(t_dda *dda, t_game *game, t_vector *vector)
{
	if (vector->x < 0)
	{
		dda->stepX = -1;
		dda->sidedistX = (game->player->posX - dda->x) * dda->deltaX;
	}
	else
	{
		dda->stepX = 1;
		dda->sidedistX = (dda->x + 1.0 - game->player->posX) * dda->deltaX;
	}
	if (vector->y < 0)
	{
		dda->stepY = -1;
		dda->sidedistY = (game->player->posY - dda->y) * dda->deltaY;
	}
	else
	{
		dda->stepY = 1;
		dda->sidedistY = (dda->y + 1.0 - game->player->posY) * dda->deltaY;
	}
}
