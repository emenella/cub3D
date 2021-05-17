#include "cub3D.h"

t_sprites	*ft_spritesnew(int x, int y)
{
	t_sprites	*sprites;

	sprites = malloc(sizeof(t_sprites));
	if (!sprites)
		return (NULL);
	sprites->x = x;
	sprites->y = y;
	sprites->next = NULL;
	return (sprites);
}

void	ft_spritesfree(t_sprites *lst)
{
	t_sprites	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst);
		lst = NULL;
		lst = tmp;
	}
}

void	ft_spritesadd_front(t_sprites **alst, t_sprites *new)
{
	if (alst != NULL)
		new->next = *alst;
	*alst = new;
}
