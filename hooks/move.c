/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:30:32 by akrache           #+#    #+#             */
/*   Updated: 2019/04/12 14:15:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	key_pressed_larrow(t_wolf *tab)
{
	tab->player->pov = (tab->player->pov + tab->player->turn) % 360;
	display(tab);
}

void	key_pressed_rarrow(t_wolf *tab)
{
	tab->player->pov = ANGLE(tab->player->pov - tab->player->turn);
	display(tab);
}


void	key_pressed_darrow(t_wolf *tab)
{
	if (tab->map->grid[(int)((tab->player->pos_y + sin(RAD(tab->player->pov)) * tab->player->speed) / SIZE)][(int)((tab->player->pos_x - cos(RAD(tab->player->pov)) * tab->player->speed) / SIZE)]->type == '0')
	{
		tab->player->pos_x -= cos(RAD(tab->player->pov)) * tab->player->speed;
		tab->player->pos_y += sin(RAD(tab->player->pov)) * tab->player->speed;
		display(tab);
	}
}

void	key_pressed_uarrow(t_wolf *tab)
{
	if (tab->map->grid[(int)((tab->player->pos_y - sin(RAD(tab->player->pov)) * tab->player->speed) / SIZE)][(int)((tab->player->pos_x + cos(RAD(tab->player->pov)) * tab->player->speed) / SIZE)]->type == '0')
	{
		tab->player->pos_x += cos(RAD(tab->player->pov)) * tab->player->speed;
		tab->player->pos_y -= sin(RAD(tab->player->pov)) * tab->player->speed;
		display(tab);
	}
}

void	key_pressed_crouch(t_wolf *tab)
{
	if (tab->player->crouch)
	{
		tab->player->crouch = 0;
		tab->player->speed = tab->player->speed << 1;
	}
	else
	{
		tab->player->crouch = 1;
		tab->player->speed = tab->player->speed >> 1;
	}
	display(tab);
}
