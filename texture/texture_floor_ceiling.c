/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clevaill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:26:23 by clevaill          #+#    #+#             */
/*   Updated: 2019/04/17 17:26:26 by clevaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void		texturise_floor_ceiling(t_wolf *tab, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH)
	{
		if (y >= 0 && y < HEIGHT)
			tab->img_adr[x + y * tab->sl] = color;
	}
}

t_texture	**parse_textures2(t_wolf *tab)
{
	t_texture **res;

	if (!(res = (t_texture **)malloc(sizeof(t_texture *) * 12)))
		return (0);
	res[1] = 0;
	res[0] = texture_init(tab, "texture/wall/wood.xpm", 0);

	return (res);
}
