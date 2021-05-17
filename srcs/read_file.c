#include "cub3D.h"

t_list	*ft_read_cub(int fd)
{
	int		ret;
	char	*line;
	t_list	*result;

	ret = get_next_line(fd, &line);
	result = ft_lstnew(line);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		ft_lstadd_back(&result, ft_lstnew(line));
	}
	return (result);
}

void	ft_format_cub(t_list **alst)
{
	t_list	*lst;
	t_list	*next;

	lst = *alst;
	while (lst->next)
	{
		next = lst->next;
		if (ft_is_empty_line(lst->content))
			ft_listfree(lst, alst);
		lst = next;
	}	
}

int	ft_is_empty_line(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] && ft_strlen(str) != 0)
		if (str[i] != '\t' && str[i] != '\n' && str[i] != '\v' && str[i] != '\f'
			&& str[i] != '\r' && str[i] != ' ')
			return (0);
	return (1);
}
