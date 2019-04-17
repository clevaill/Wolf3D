/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:29:40 by akrache           #+#    #+#             */
/*   Updated: 2019/04/16 16:48:39 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void		display(t_wolf *tab)
{
	int		x;
	double	angle;
	double	dist;
	double	cons;

	x = WIDTH - 1;
	angle = ANGLE((tab->player->pov - (FOV >> 1)));
	dist = 0;
	while (x >= 0)
	{
		cast_ray(tab, angle, x);
		x--;
		angle += RAY_ANGLE;
		angle >= 360.0 ? angle -= 360.0 : 0;
	}
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img_ptr, 0, 0);
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->tex[10]->img_ptr, WIDTH >> 1, HEIGHT - 256);
	/*mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 10, 0xFFFFFF, ft_itoa(tab->player->pov));
	mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 30, 0xFFFFFF, ft_itoa(tab->player->pos_x));
	mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 50, 0xFFFFFF, ft_itoa(tab->player->pos_y));
	mlx_string_put(tab->mlx_ptr, tab->win_ptr, 50, 30, 0xFFFFFF, ft_itoa(tab->player->pos_x / SIZE));
	mlx_string_put(tab->mlx_ptr, tab->win_ptr, 50, 50, 0xFFFFFF, ft_itoa(tab->player->pos_y / SIZE));*/
}
