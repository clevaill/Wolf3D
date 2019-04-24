/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:53:34 by akrache           #+#    #+#             */
/*   Updated: 2019/04/24 12:56:34 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int			light(int color, double dist)
{
	double lumos;

	lumos = (SIZE >> 1) / dist;
	lumos > 0.30 ? lumos = 0.30 : 0;
	if (lumos < 0.01)
		return (color);
	return((int)((color & 0xff) + lumos * (31 - (color & 0xff)))
	+ ((int)((color >> 8 & 0xff) + lumos * (127 - (color >> 8 & 0xff))) << 8)
	+ ((int)((color >> 16 & 0xff) + lumos * (255 - (color >> 16 & 0xff))) << 16));
}

int			shading(int color, double dist)
{
	double shade;

	shade = (SIZE << 2) / dist;
	if (shade > 1)
		return (color);
	return ((int)(shade * (color & 0xff)) + ((int)(shade
		* (color >> 8 & 0xff)) << 8) + ((int)(shade * (color >> 16 & 0xff)) << 16));
}

void		texturise_wall(t_wolf *tab, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH)
	{
		if (y >= 0 && y < HEIGHT)
			tab->img_adr[x + y * tab->sl] = color;
	}
}

t_texture	*texture_init(t_wolf *tab, char *file, unsigned char id)
{
	t_texture *t;

	if (!(t = (t_texture *)malloc(sizeof(t_texture))))
		return (0);
	if (!(t->img_ptr = mlx_xpm_file_to_image(tab->mlx_ptr, file, &(t->width), &(t->height))))
		return (0);
	t->img_adr = (unsigned int *)mlx_get_data_addr(t->img_ptr,
		&(t->bpp), &(t->sl), &(t->endian));
	t->id = id;
	t->sl = t->sl >> 2;
	return (t);
	
}

t_texture	**parse_textures(t_wolf *tab)
{
	t_texture **res;

	if (!(res = (t_texture **)malloc(sizeof(t_texture *) * 14)))
		return (0);
	res[13] = 0;
	//walls//
	res[0] = texture_init(tab, "texture/wall/void.xpm", 0);
	res[1] = texture_init(tab, "texture/wall/wood.xpm", 1);
	res[2] = texture_init(tab, "texture/wall/redbrick.xpm", 2);
	res[3] = texture_init(tab, "texture/wall/bluestone.xpm", 3);
	res[4] = texture_init(tab, "texture/wall/bricks.xpm", 4);
	res[5] = texture_init(tab, "texture/wall/colorstone.xpm", 5);
	res[6] = texture_init(tab, "texture/wall/eagle.xpm", 6);
	res[7] = texture_init(tab, "texture/wall/greystone.xpm", 7);
	res[8] = texture_init(tab, "texture/wall/mossy.xpm", 8);
	//sprites//
	res[9] = texture_init(tab, "texture/sprites/jagpistol.xpm", 9);
	res[10] = texture_init(tab, "texture/sprites/shotgun.xpm", 10);
	res[11] = texture_init(tab, "texture/sprites/pause.xpm", 11);
	res[12] = texture_init(tab, "texture/sprites/credit.xpm", 12);
	return (res);
}