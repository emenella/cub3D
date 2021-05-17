#include "cub3D_bonus.h"

void	ft_write_header(t_image *img, int fd)
{
	int	offset;
	int	size;

	offset = 54;
	size = offset + img->width * img->height * 4;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &offset, 4);
}

void	ft_write_image_header(t_image *img, int fd)
{
	int	sizeheader;
	int	plan;
	int	size;

	plan = 1;
	sizeheader = 40;
	size = img->width * img->height;
	write(fd, &sizeheader, 4);
	write(fd, &img->width, 4);
	write(fd, &img->height, 4);
	write(fd, &plan, 2);
	write(fd, &img->bits_per_pixel, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

void	ft_write_image(t_image *img, int fd)
{
	int	y;
	int	x;
	int	c;

	y = img->height;
	while (--y >= 0)
	{
		x = -1;
		while (++x < img->width)
		{
			c = img->addr[y * img->line_length + x * img->bits_per_pixel / 8];
			write(fd, &c, 1);
			c = img->addr[y * img->line_length + x
				* img->bits_per_pixel / 8 + 1];
			write(fd, &c, 1);
			c = img->addr[y * img->line_length + x
				* img->bits_per_pixel / 8 + 2];
			write(fd, &c, 1);
			write(fd, "\0", 1);
		}
	}
}

void	ft_save(t_image *img)
{
	int	fd;

	fd = open("save.bmp", O_CREAT | O_RDWR, 0666);
	ft_write_header(img, fd);
	ft_write_image_header(img, fd);
	ft_write_image(img, fd);
	close(fd);
}
