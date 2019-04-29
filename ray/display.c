/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:29:40 by akrache           #+#    #+#             */
/*   Updated: 2019/04/27 16:56:36 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

double		rad(double angle)
{
	return (angle * (M_PI / 180.0));
}

/*
static void	switch_hand(t_wolf *tab)
{
	int i;

	if (tab->player->hand)
	{
		i = 1;
		while (i < tab->player->hand->height)
		{
			mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img_ptr, 0, 0);
			mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->player->hand->img_ptr, WIDTH >> 1, HEIGHT - tab->player->hand->height + i);
			i++;
			usleep(3000);
		}
		tab->player->hand = 0;
	}
	else
	{
		tab->player->hand = tab->tex[10];
		i = 1;
		while (i < tab->player->hand->height)
		{
			mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img_ptr, 0, 0);
			mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->player->hand->img_ptr, WIDTH >> 1, HEIGHT - i);
			i++;
			usleep(3000);
		}
	}
	tab->swtch = 0;
}
*/
static void	display_sprites(t_wolf *tab)
{
	//if (tab->swtch)
	//	switch_hand(tab);
	//if (tab->player->hand)
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->player->hand->img_ptr, WIDTH >> 1, HEIGHT - tab->player->hand->height);
	if (tab->pause)
	{
		mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->tex[11]->img_ptr, (WIDTH >> 1) - (tab->tex[11]->width >> 1), (HEIGHT >> 1) - (tab->tex[11]->height >> 1));
		mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->tex[12]->img_ptr, (WIDTH >> 1) - (tab->tex[12]->width >> 1), (HEIGHT) - (tab->tex[12]->height));
	}
	mlx_string_put(tab->mlx_ptr, tab->win_ptr, 10, 10, 0xFFFFFF, ft_itoa(tab->player->pov));//
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
