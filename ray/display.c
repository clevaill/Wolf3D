/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:29:40 by akrache           #+#    #+#             */
/*   Updated: 2019/04/24 13:28:22 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

double		rad(double angle)
{
	return (angle * (M_PI / 180.0));
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
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->tex[10]->img_ptr, WIDTH >> 1, HEIGHT - 177);
	if (tab->pause)
	{
		mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->tex[11]->img_ptr, (WIDTH >> 1) - (tab->tex[11]->width >> 1), (HEIGHT >> 1) - (tab->tex[11]->height >> 1));
		mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->tex[12]->img_ptr, (WIDTH >> 1) - (tab->tex[12]->width >> 1), (HEIGHT) - (tab->tex[12]->height));
	}
	mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 10, 0xFFFFFF, ft_itoa(tab->player->pov));//
	//mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 30, 0xFFFFFF, ft_itoa(tab->player->pos_x));
	//mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 50, 0xFFFFFF, ft_itoa(tab->player->pos_y));
}
