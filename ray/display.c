/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:29:40 by akrache           #+#    #+#             */
/*   Updated: 2019/05/02 17:10:59 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

double		rad(double angle)
{
	return (angle * (M_PI / 180.0));
}

int			get_id(t_wolf *tab, double a, t_coord v, int verti)
{
	if (verti)
	{
		if (a >= 90 && a <= 270)
			return (tab->map->grid[(int)v.y / SIZE][(int)v.x / SIZE].east);
		else
			return (tab->map->grid[(int)v.y / SIZE][(int)v.x / SIZE].west);
	}
	else
	{
		if (a >= 180)
			return (tab->map->grid[(int)v.y / SIZE][(int)v.x / SIZE].north);
		else
			return (tab->map->grid[(int)v.y / SIZE][(int)v.x / SIZE].south);
	}
	return (0);
}

static void	display_sprites(t_wolf *tab)
{
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr,
		tab->player->hand.img_ptr,
		(WIDTH + (tab->player->hand.id == 10 ?
		tab->player->hand.width : 0)) >> 1, HEIGHT - tab->player->hand.height);
	if (tab->pause)
	{
		mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr,
			tab->tex[11].img_ptr, (WIDTH >> 1) - (tab->tex[11].width >> 1),
			(HEIGHT >> 1) - (tab->tex[11].height >> 1));
		mlx_put_image_to_window(tab->mlx_ptr,
			tab->win_ptr, tab->tex[12].img_ptr,
			(WIDTH >> 1) - (tab->tex[12].width >> 1),
			HEIGHT - tab->tex[12].height);
	}
}

void		display(t_wolf *tab)
{
	int		x;
	double	angle;
	double	dist;

	x = WIDTH - 1;
	angle = (tab->player->pov - (FOV >> 1));
	angle < 0 ? angle += 360.0 : 0;
	dist = 0;
	while (x >= 0)
	{
		cast_ray(tab, angle, x);
		x--;
		angle += RAY_ANGLE;
		angle >= 360.0 ? angle -= 360.0 : 0;
	}
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img_ptr, 0, 0);
	display_sprites(tab);
}
