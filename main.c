/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:20:45 by akrache           #+#    #+#             */
/*   Updated: 2019/04/27 19:38:24 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		wolf_usage(int r)
{
	ft_putendl("usage: ./wolf <map>");
	return (r);
}

t_player		*player_init(t_wolf *tab, int x, int y, double pov)
{
	t_player	*res;

	if (!(res = (t_player *)malloc(sizeof(t_player))))
		return (0);
	res->hand = tab->tex[10];
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
	tab->img_adr = (unsigned int *)mlx_get_data_addr(tab->img_ptr,
	&(tab->bpp), &(tab->sl), &(tab->endian));
	tab->sl = tab->sl >> 2;
	tab->pause = 0;
	tab->swtch = 0;
	tab->fov_rad = rad(FOV);
	tab->cons = SIZE * (int)((WIDTH / 2) / tan(tab->fov_rad / 2));
	tab->map = map;
	tab->tex = parse_textures(tab);
	if (!tab->tex)
		return (0);
	tab->player = player_init(tab, 5, 5, 0);
	return (tab);
}

static void		hooks(t_wolf *tab)
{
	mlx_hook(tab->win_ptr, 2, 0, key_hook, tab);
	mlx_hook(tab->win_ptr, 17, 0, key_pressed_esc, tab);
}

/*
void			test_map(t_map *map)
{
	int i;
	int j;

	printf("x = %d | y = %d\n", map->width, map->height);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			//printf("i = %d | j = %d\n", i, j);
			//printf("w = %d | f = %d | c = %d\n", map->grid[i][j].type, map->grid[i][j].floor, map->grid[i][j].ceil);
			//printf("x = %d | y = %d\n", i, j);
			printf("%d ", map->grid[i][j].south);
			j++;
		}
		printf("\n");
		i++;
	}
}*/

int				main(int argc, char *argv[])
{
	t_wolf	*tab;
	t_map	*map;

	if (argc != 2)
		return (wolf_usage(0));
	if (!(map = parsing(argv[1])))
		return (0);
	//test_map(map);
	if (!(tab = tab_init(map)))
		return (0);
	display(tab);
	hooks(tab);
	mlx_loop(tab->mlx_ptr);
	return (0);
}
