#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include "../minilibx/mlx.h"
# include "../libft/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

# define BLOCK "102NSWE"
# define MALLOC_ERROR "Error: malloc failed\n"
# define MAP_ERROR "Error: wrong map\n"

typedef enum e_block
{
	SPACE,
	WALL,
	OBJECT,
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_block;

typedef struct s_vector {
	float	x;
	float	y;
}	t_vector;

typedef struct s_vector_int {
	int	x;
	int	y;
}	t_vector_int;

typedef struct s_draw {
	int				x;
	int				y;
	int				drawStart;
	int				drawEnd;
	int				lineHeight;
	int				spriteWidth;
	int				spriteHeight;
	int				spriteScreenX;
	float			invdet;
	unsigned int	color;
}	t_draw;

typedef struct s_sprite
{
	int				y;
	int				textY;
	int				textX;
	float			spriteX;
	float			spriteY;
	float			transformX;
	float			transformY;
	float			invdet;
	unsigned int	color;
	int				drawEndX;
	int				drawStartX;
	int				spriteWidth;
	int				drawEndY;
	int				drawStartY;
	int				spriteHeight;
	int				spriteScreenX;
}	t_sprite;

typedef struct s_dda
{
	float		stepX;
	float		stepY;
	int			side;
	float		deltaX;
	float		deltaY;
	float		sidedistX;
	float		sidedistY;
	int			x;
	int			y;
}	t_dda;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		widthsquare;
	int		heightsquare;
	int		width;
	int		height;		
}	t_image;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	t_image		*minimap;
	t_image		*screen;
}	t_mlx;

typedef struct s_texture {
	char		*path;
	t_image		*img;
}	t_texture;

typedef struct s_RGB {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	t;
}	t_RGB;

typedef struct s_map {
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_wall {
	t_texture	*NO;
	t_texture	*SO;
	t_texture	*WE;
	t_texture	*EA;
}	t_wall;

typedef struct s_player {
	float		posX;
	float		posY;
	t_vector	*dir;
	t_vector	*plane;
	t_vector	*camera;
	t_vector	*ray;
	float		speed;
	float		rot;
	int			input_front;
	int			input_side;
	int			input_rotate;
}	t_player;

typedef struct s_sprites {
	int					x;
	int					y;
	struct s_sprites	*next;
}	t_sprites;

typedef struct s_game {
	int			width;
	int			height;
	t_wall		*wall;
	t_mlx		*mlx;
	t_texture	*sprite;
	t_RGB		*floor;
	t_RGB		*ceiling;
	t_map		*map;
	t_player	*player;
	int			save;
}	t_game;

t_game		*ft_parser_cub(t_list *cub);
t_list		*ft_read_cub(int fd);
void		ft_format_cub(t_list **alst);
void		ft_listfree(t_list *lst, t_list **alst);
int			ft_is_empty_line(char *str);
t_game		*ft_init_game(void);
t_texture	*ft_init_texture(char *path);
void		ft_parser_resolution(t_list *cub, t_game *game);
void		ft_parser_texture(t_list *cub, t_game *game);
void		ft_parser_color(t_list *cub, t_game *game);
void		ft_parser_map(t_list **cub, t_game *game);
int			ft_argchr(t_list *cub);
t_RGB		*ft_init_RGB(int r, int g, int b, int t);
void		ft_exit(char *str, t_game *game);
int			ft_max_line(t_list **cub);
t_map		*ft_init_map(char **result, int height, int width);
int			ft_isspace_touch(t_map *map, int i, int j);
int			ft_verification_game(t_game *game);
void		ft_free_double_array(char **str, int n);
t_wall		*ft_init_wall(void);
void		ft_mlx_init_texture(t_game *game);
t_player	*ft_init_player(char c, int i, int j);
void		my_mlx_pixel_put(t_image *data, int x, int y, unsigned int color);
void		ft_map_to_image(t_mlx *mlx, t_game *game);
void		ft_draw_square(t_image *data, int size, int center_y, int center_x);
void		ft_my_mlx_loop(t_game *game);
int			ft_my_mlx_hook(int keycode, t_game *game);
t_mlx		*ft_init_mlx(void);
t_vector	*ft_init_vector(double x, double y);
t_vector	*ft_create_vector_angle(t_vector *v, double angle);
double		ft_degres_to_radian(double degres);
void		ft_ray(t_game *game, t_vector *vector, int pixel);
int			rendu(t_game *game);
void		ft_fov(t_game *game, int w);
void		ft_rotate_player_right(t_player *p);
void		ft_rotate_player_left(t_player *p);
void		ft_draw_line_verticale(t_image *data, t_draw *draw,
				unsigned int color);
t_image		*ft_init_image(void *mlx, int width, int height);
void		ft_mlx_get_address_texture(t_game *game);
void		ft_draw_wall_texture(t_game *game, int side,
				double wallx, t_draw *draw);
t_sprites	*ft_spritesnew(int x, int y);
void		ft_spritesfree(t_sprites *lst);
void		ft_spritesadd_front(t_sprites **alst, t_sprites *new);
void		ft_sprite(t_sprites **sprites, t_game *game, int pixel);
t_sprites	*ft_spriteslast(t_sprites *lst);
int			ft_finder(char *src, char *find);
void		ft_free_image(t_mlx *mlx, t_image *img);
void		ft_free_texture(t_texture *texture, t_mlx *mlx);
void		ft_free_map(t_map *map);
void		ft_free_player(t_player *player);
void		ft_free_game(t_game *game);
void		ft_free_wall(t_wall *wall, t_mlx *mlx);
void		ft_free_mlx(t_mlx *mlx);
void		ft_save(t_image *img);
void		ft_add_c(int i, char **str, char c, int len);
void		ft_draw_player_on_minimap(t_game *game);
void		ft_init_minimap(t_game *game);
int			ft_close(t_game *game);
t_draw		*ft_init_draw(int x, int drawStart, int drawEnd, int lineHeight);
void		ft_draw_ceilling_floor(t_game *game, t_draw *draw);
long int	create_trgb(unsigned long int t, unsigned long int r,
				unsigned long int g, unsigned long int b);
int			ft_get_distance(t_game *game, t_vector *vector,
				t_sprites **sprites, float *walldist);
void		ft_calcul_sprite(t_sprite *d, t_game *game, t_sprites *lst);
void		ft_dda(t_dda *dda, t_game *game, t_sprites **sprites);
void		ft_init_step(t_dda *dda, t_game *game, t_vector *vector);
void		ft_move1(t_game *game);
void		ft_move(t_game *game);
t_image		*ft_select_texture(t_game *game, int *textX, double wallx,
				int side);
t_vector	*ft_set_dir(char c);
void		ft_fps(t_game *game);
void		ft_draw_sprite(t_sprite *s, int *d, t_game *game, int x);
int			ft_my_mlx_unhook(int keycode, t_game *game);
#endif