/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:03:23 by akrache           #+#    #+#             */
/*   Updated: 2019/04/05 15:03:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	key_pressed_f(t_wolf *tab)
{
	tab->player->look -= 10;
	display(tab);
}

void	key_pressed_r(t_wolf *tab)
{
	tab->player->look += 10;
	display(tab);
}
