/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:20:45 by akrache           #+#    #+#             */
/*   Updated: 2019/04/12 14:02:52 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#include <stdio.h>
static int		wolf_usage(int r)
{
	ft_putendl("usage: ./wolf <map>");
	return (r);
}

t_player		*player_init(int x, int y, double pov)
{
	t_player	*res;
	if (!(res = (t_player *)malloc(sizeof(t_player))))
		return (0);
	res->pos_x = x * SIZE + SIZE / 2;
	res->pos_y = y * SIZE + SIZE / 2;
	res->pov = pov;
	res->height = SIZE / 2;
	res->speed = SIZE / 4;
	res->turn = 10;
	res->look = 0;
	res->crouch = 0;
	return (res);
}

static t_wolf	*tab_init(t_map *map)
{
	t_wolf *tab;

	if (!(tab = (t_wolf *)malloc(sizeof(t_wolf))))
		return (0);
	tab->mlx_ptr = mlx_init();
	tab->win_ptr = mlx_new_window(tab->mlx_ptr, WIDTH, HEIGHT, "Wolf3D");
	tab->img_ptr = mlx_new_image(tab->mlx_ptr, WIDTH, HEIGHT);
	tab->img_adr = mlx_get_data_addr(tab->img_ptr,
	&(tab->bpp), &(tab->sl), &(tab->endian));
	tab->player = player_init(5, 2, 220);
	tab->map = map;
	tab->tex = parse_textures(tab);
	if(!tab->tex)
		ft_putendl("NOPE");
	return (tab);
}

static void		hooks(t_wolf *tab)
{
	mlx_hook(tab->win_ptr, 2, 0, key_hook, tab);
	//mlx_hook(tab->win_ptr, 4, 0, mouse_press, tab);
	//mlx_hook(tab->win_ptr, 6, 0, mouse_move, tab);
	mlx_hook(tab->win_ptr, 17, 0, key_pressed_esc, tab);
}

void			test_grid(t_map *map)
{
	int i;
	int j;

	i = 0;
	while ( i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			write(1,map->grid[i][j],1);
			j++;
		}
		write(1, " \n", 1);
		i++;
	}
}

int				main(int argc, char *argv[])
{
	t_wolf	*tab;
	t_map	*map;

	if (argc != 2)
		return (wolf_usage(0));
	//PARSING
	if (!(map = map_init(argv[1])))
		return (0);
	if (!(tab = tab_init(map)))
		return (0);
	printf("FOV = %d, FOV_RAD = %f, DISTANCE = %d, RAY_ANGLE = %f\n", FOV, FOV_RAD, DISTANCE, RAY_ANGLE);
	display(tab);
	hooks(tab);
	mlx_loop(tab->mlx_ptr);
	return (0);
}
