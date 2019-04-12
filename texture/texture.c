/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:53:34 by akrache           #+#    #+#             */
/*   Updated: 2019/04/12 12:38:01 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void		texturise_wall(t_wolf *tab, int *to, int *fr, char id)
{
	int		j;
	int		c1;
	int		c2;

	
	if (to[0] >= 0 && to[0] < WIDTH)
	{
		if (to[1] >= 0 && to[1] < HEIGHT)
		{
			c1 = tab->bpp >> 3;
			c2 = tab->tex[id]->bpp >> 3;
			j = -1;
			while (++j < 4)
			{
				tab->img_adr[to[0] * c1 + to[1] * tab->sl + j]
				= tab->tex[id]->img_adr[fr[0] * c2 + fr[1] * tab->tex[id]->sl + j];
			}
		}
	}
}

t_texture	*texture_init(t_wolf *tab, char *file, unsigned char id)
{
	t_texture *t;

	if (!(t = (t_texture *)malloc(sizeof(t_texture))))
		return (0);
	t->img_ptr = mlx_xpm_file_to_image(tab->mlx_ptr, file, &(t->width), &(t->height));
	if (!t->img_ptr)
		return (0);
	t->img_adr = mlx_get_data_addr(t->img_ptr,
		&(t->bpp), &(t->sl), &(t->endian));
	t->id = id;
	//printf("%d | %d\n", t->height, t->width);
	return (t);
	
}

t_texture	**parse_textures(t_wolf *tab)
{
	t_texture **res;

	if (!(res = (t_texture **)malloc(sizeof(t_texture *) * 10)))
		return (0);
	res[9] = 0;
	res[0] = texture_init(tab, "texture/pics/purplestone.xpm", 0);
	res[1] = texture_init(tab, "texture/pics/wood.xpm", 1);
	res[2] = texture_init(tab, "texture/pics/redbrick.xpm", 2);
	res[3] = texture_init(tab, "texture/pics/bluestone.xpm", 3);
	res[4] = texture_init(tab, "texture/pics/bricks.xpm", 4);
	res[5] = texture_init(tab, "texture/pics/colorstone.xpm", 5);
	res[6] = texture_init(tab, "texture/pics/eagle.xpm", 6);
	res[7] = texture_init(tab, "texture/pics/greystone.xpm", 7);
	res[8] = texture_init(tab, "texture/pics/mossy.xpm", 8);
	return (res);
}