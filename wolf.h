/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:31:51 by akrache           #+#    #+#             */
/*   Updated: 2019/04/15 19:09:18 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

# define BUFF_SIZE 4096
# define WIDTH 1600//1440//
# define HEIGHT 900//810/
# define RAD(angleInDegrees) ((angleInDegrees) * (M_PI / 180.0))
# define DEG(angleInRadians) ((angleInRadians) * (180.0 / M_PI))
# define ANGLE(x) (int)(x < 0 ? 360.0 + x : x)
# define SIZE 64
# define FOV 60
# define FOV_RAD RAD(FOV)
# define DISTANCE (int)((WIDTH / 2) / tan(FOV_RAD / 2))
# define RAY_ANGLE ((double)FOV / WIDTH)
# define CONS SIZE * DISTANCE
# define SHADE(x) (SIZE << 2) / x

typedef struct		s_coord
{
	double			x;
	double			y;
}					t_coord;

typedef struct		s_player
{
	int				pos_x;
	int				pos_y;
	int				height;
	int				pov;
	int				turn;
	int				speed;
	int				look;
	char			crouch;
}					t_player;

typedef struct		s_block
{
	char			type;
	char			texture;
}					t_block;

typedef struct		s_map
{
	int				width;
	int				height;
	t_block			***grid;
}					t_map;

typedef struct		s_texture
{
	void			*img_ptr;
	unsigned int	*img_adr;
	int				bpp;
	int				sl;
	int				endian;
	int				width;
	int				height;
	unsigned char	id;
}					t_texture;

typedef struct		s_wolf
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned int	*img_adr;
	int				bpp;
	int				sl;
	int				endian;
	t_player		*player;
	t_map			*map;
	t_texture		**tex;
}					t_wolf;

/*
typedef struct		s_ray
{
	unsigned int	x;
	unsigned int	y;
	char			vh;

}					t_ray;
*/

/*
** RAY
*/

//void			img_pixel_put(t_wolf *tab, int x, int y, int c);
void				cast_ray(t_wolf *tab, double angle, int x);
void				display(t_wolf *tab);

/*
** KEYS
*/

int					mouse_move(int x, int y, t_wolf *tab);
int					key_hook(int keycode, t_wolf *tab);
int					key_pressed_esc(t_wolf *tab);
void				key_pressed_del(t_wolf *tab);
void				key_pressed_larrow(t_wolf *tab);
void				key_pressed_rarrow(t_wolf *tab);
void				key_pressed_uarrow(t_wolf *tab);
void				key_pressed_darrow(t_wolf *tab);
void				key_pressed_crouch(t_wolf *tab);
void				key_pressed_r(t_wolf *tab);
void				key_pressed_f(t_wolf *tab);

/*
** PARSING
*/

t_map				*map_init(char *arg);

/*
** TEXTURE
*/

int					shading(int color, double shade);
t_texture			**parse_textures(t_wolf *tab);
t_texture			*texture_init(t_wolf *tab, char *file, unsigned char id);
void				texturise_wall(t_wolf *tab, int x, int y, int color);

#endif
