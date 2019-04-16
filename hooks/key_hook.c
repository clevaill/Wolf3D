/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:28:44 by akrache           #+#    #+#             */
/*   Updated: 2019/04/15 18:24:16 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		key_hook(int keycode, t_wolf *tab)
{
	if (keycode == 53)
		key_pressed_esc(tab);
	else if (keycode == 51)
		key_pressed_del(tab);
	else if (keycode == 123 || keycode == 0)
		key_pressed_larrow(tab);
	else if (keycode == 124 || keycode == 2)
		key_pressed_rarrow(tab);
	else if (keycode == 125 || keycode == 1)
		key_pressed_darrow(tab);
	else if (keycode == 126 || keycode == 13)
		key_pressed_uarrow(tab);
	else if (keycode == 259)
		key_pressed_crouch(tab);
	else if (keycode == 15)
		key_pressed_r(tab);
	else if (keycode == 3)
		key_pressed_f(tab);
	return (keycode);
}

void	key_pressed_del(t_wolf *tab)
{
	mlx_clear_window(tab->mlx_ptr, tab->win_ptr);
	ft_bzero(tab->img_adr, WIDTH * HEIGHT);
}

int		key_pressed_esc(t_wolf *tab)
{
	key_pressed_del(tab);
	mlx_destroy_image(tab->mlx_ptr, tab->img_ptr);
	mlx_destroy_window(tab->mlx_ptr, tab->win_ptr);
	free(tab->mlx_ptr);
	free(tab);
	ft_putstr("Exiting program\n");
	exit(0);
}

/*
int	mouse_move(int x, int y, t_wolf *tab)
{
	int u;
	int v;

	u = tab->x - x;;
	v = tab->y - y;
	if (u > 0 && x < (WIDTH >> 1))
		key_pressed_larrow(tab);
	else if (u < 0 && x > (WIDTH >> 1))
		key_pressed_rarrow(tab);
	//if (v > 0)
	//	key_pressed_r(tab);
	//else
	//	key_pressed_f(tab);
	tab->x = x;
	tab->y = y;
	//mlx_string_put(tab->mlx_ptr, tab->win_ptr, WIDTH - 100, 30, 0xFFFFFF, ft_itoa(x));
	//mlx_string_put(tab->mlx_ptr, tab->win_ptr, WIDTH - 100, 50, 0xFFFFFF, ft_itoa(y));
	return (0);
}
*/