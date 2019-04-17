/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:33:32 by akrache           #+#    #+#             */
/*   Updated: 2019/04/16 16:23:21 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

static void		img_pixel_put(t_wolf *tab, int x, int y, int c)
{
	if (x >= 0 && x < WIDTH)
	{
		if (y >= 0 && y < HEIGHT)
			tab->img_adr[x + y * tab->sl] = c;
	}
}

static t_coord	*horizontal_checking(t_wolf *tab, double a, t_coord *res)
{
	double		x;
	double		y;
	double		xa;
	double		ya;

	if (a > 180.0)
		y = (tab->player->pos_y / SIZE + 1) * SIZE;
	else
		y = (tab->player->pos_y / SIZE) * SIZE - 1;
	x = (tab->player->pos_x + (tab->player->pos_y - y) / tan(RAD(a)));
	ya = a > 180.0 ? SIZE : -SIZE;
	xa = a > 180.0 ? -(SIZE / tan(RAD(a))) : (SIZE / tan(RAD(a)));
	while ((x >= 0 && x < tab->map->width * SIZE)
		&& (y >= 0 && y < tab->map->height * SIZE)
		&& tab->map->grid[(int)(y / SIZE)][(int)(x / SIZE)]->type == '0')
	{
		x += xa;
		y += ya;
	}
	res->x = x;
	res->y = y;
	return (res);
}

static t_coord	*vertical_checking(t_wolf *tab, double a, t_coord *res)
{
	double		x;
	double		y;
	double		xa;
	double		ya;

	if (a >= 90.0 && a <= 270.0)
		x = (tab->player->pos_x / SIZE) * SIZE - 1;
	else
		x = (tab->player->pos_x / SIZE + 1) * SIZE;
	y = (tab->player->pos_y + (tab->player->pos_x - x) * tan(RAD(a)));
	xa = (a >= 90.0 && a <= 270.0) ? -SIZE : SIZE;
	ya = a < 90.0 || a > 270.0 ? -(SIZE * tan(RAD(a))) : (SIZE * tan(RAD(a)));
	while ((x >= 0 && x < tab->map->width * SIZE)
		&& (y >= 0 && y < tab->map->height * SIZE)
		&& tab->map->grid[(int)(y / SIZE)][(int)(x / SIZE)]->type == '0')
	{
		x += xa;
		y += ya;
	}
	res->x = x;
	res->y = y;
	return (res);
}

static void		slice(t_wolf *tab, int x, double dist, int offset, int id)
{
	int			p;
	int			y;
	int			top;
	double		shade;
	double		lumos;

	p = (int)(CONS / dist);
	top = ((HEIGHT - p) / (tab->player->crouch ? 1.4 : 2)) + tab->player->look;
	y = -1;
	while (++y < top)
		img_pixel_put(tab, x, y, 0x7ADDF6); //ceiling texture
	while (y < top + p)
	{
		(shade = SHADE(dist)) > 1 ? shade = 1 : 0;
		(lumos = LIGHT(dist)) > 1 ? lumos = 0 : 0;
		texturise_wall(tab, x, y, light(shading(tab->tex[id]->img_adr[(offset
		+ (((y - top) * tab->tex[id]->height) / p) * tab->tex[id]->sl)], shade), lumos));
		y++;
	}
	while (y < HEIGHT)
	{
		//floor texture
		img_pixel_put(tab, x, y, 0x909090);
		y++;
	}
}

void			cast_ray(t_wolf *tab, double a, int x)
{
	double	d_v;
	double	d_h;
	t_coord	v;
	t_coord	h;

	vertical_checking(tab, a, &v);
	horizontal_checking(tab, a, &h);
	d_v = sqrt((v.x - tab->player->pos_x) * (v.x - tab->player->pos_x) +
		(v.y - tab->player->pos_y) * (v.y - tab->player->pos_y))
		* cos(RAD((a - tab->player->pov)));
	d_h = sqrt((h.x - tab->player->pos_x) * (h.x - tab->player->pos_x) +
		(h.y - tab->player->pos_y) * (h.y - tab->player->pos_y))
		* cos(RAD((a - tab->player->pov)));
	if (d_v < d_h)
		slice(tab, x, d_v, (int)v.y % SIZE,
		tab->map->grid[(int)v.y / SIZE][(int)v.x / SIZE]->type - '0');
	else
		slice(tab, x, d_h, (int)h.x % SIZE,
		tab->map->grid[(int)h.y / SIZE][(int)h.x / SIZE]->type - '0');
}
