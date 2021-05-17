#include "cub3D_bonus.h"

int	ft_max_line(t_list **cub)
{
	size_t	max;
	t_list	*lst;

	max = 0;
	lst = *cub;
	while (lst)
	{
		if (ft_strlen(lst->content) > max)
			max = ft_strlen(lst->content);
		lst = lst->next;
	}
	return (max);
}

t_map	*ft_init_map(char **result, int height, int width)
{
	t_map	*p;

	p = malloc(sizeof(t_map));
	if (!p)
		return (NULL);
	p->map = result;
	p->height = height;
	p->width = width;
	return (p);
}
