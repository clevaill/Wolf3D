/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:59:25 by akrache           #+#    #+#             */
/*   Updated: 2019/04/29 20:44:42 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	*free_player(t_player *player)
{
	free(player);
	player = 0;
	return (0);
}

void	*free_grid(t_map *map, int height)
{
	int j;

	j = 0;
	while (j < height)
	{
		if (map->grid[j])
			free(map->grid[j]);
		j++;
	}
	free(map->grid);
	map->grid = 0;
	return (0);
}

void	*free_map(t_map *map)
{
	if (map)
	{
		if (map->grid)
			free_grid(map, map->height);
		free(map);
		map = 0;
	}
	return (0);
}

void	*free_tex(t_wolf *tab, t_texture *tex)
{
	if (tex)
	{
		mlx_destroy_image(tab->mlx_ptr, tex->img_ptr);
		free(tex);
		tex = 0;
	}
	return (0);
}

void	*free_wolf(t_wolf *tab)
{
	if (tab)
	{
		if (tab->player)
			free_player(tab->player);
		if (tab->map)
			free_map(tab->map);
		if (tab->tex)
			free_tex(tab, tab->tex);
		mlx_destroy_image(tab->mlx_ptr, tab->img_ptr);
		mlx_destroy_window(tab->mlx_ptr, tab->win_ptr);
		free(tab->mlx_ptr);
		free(tab);
		tab = 0;
	}
	return (0);
}
