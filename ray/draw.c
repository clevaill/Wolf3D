/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:33:32 by akrache           #+#    #+#             */
/*   Updated: 2019/04/12 12:46:56 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

static void		img_pixel_put(t_wolf *tab, int x, int y, int c)
{
	int i;
	int cons;

	if (x >= 0 && x < WIDTH)
	{
		if (y >= 0 && y < HEIGHT)
		{
			cons = (tab->bpp >> 3);
			i = 0;
			while (i < cons)
			{
				tab->img_adr[x * cons + (y * tab->sl) + i] = c & 255;
				i++;
				c = c >> 8;
			}
		}
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
	xa = (SIZE / tan(RAD(a)));
	a > 180 ? xa = -xa : 0;
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
	ya = (SIZE * tan(RAD(a)));
	a < 90 || a > 270 ? ya = -ya : 0;
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

static void		slice(t_wolf *tab, int i, double dist, int offset, char id)
{
	int		p;
	int		to[2];
	int		from[2];
	int		y;
	int		top;

	p = (int)(CONS / dist);
	top = ((HEIGHT - p) / (tab->player->crouch ? 1.4 : 2)) + tab->player->look;
	to[0] = i;
	from[0] = offset;
	y = -1;
	while (++y < top)
		img_pixel_put(tab, i, y, 0x7ADDF6);
	while (y < top + p)
	{
		to[1] = y;
		from[1] = ((y - top) * tab->tex[id]->height) / p;
		texturise_wall(tab, to, from, id);
		y++;
	}
	while (y < HEIGHT)
	{
		img_pixel_put(tab, i, y, 0x909090);
		y++;
	}
}

void			cast_ray(t_wolf *tab, double a, int i)
{
	double	d_v;
	double	d_h;
	t_coord	v;
	t_coord	h;

	vertical_checking(tab, a, &v);
	horizontal_checking(tab, a, &h);
	d_v = sqrt(pow(v.x - tab->player->pos_x, 2) +
		pow(v.y - tab->player->pos_y, 2));
	d_h = sqrt(pow(h.x - tab->player->pos_x, 2) +
		pow(h.y - tab->player->pos_y, 2));
	if (d_v < d_h)
		slice(tab, i, d_v * cos(RAD((a - tab->player->pov))), (int)v.y % SIZE,
		tab->map->grid[(int)v.y / SIZE][(int)v.x / SIZE]->type - '0');
	else
		slice(tab, i, d_h * cos(RAD((a - tab->player->pov))), (int)h.x % SIZE,
		tab->map->grid[(int)h.y / SIZE][(int)h.x / SIZE]->type - '0');
}

/*
static t_coord	*horizontal_checking(t_wolf *tab, double a)
{
	double		x;
	double		y;
	double		xa;
	double		ya;
	t_coord	*res;

	if (!(res = (t_coord *)malloc(sizeof(t_coord))))
		return (0);
	if (a > 180.0)
		y = (tab->player->pos_y / SIZE + 1) * SIZE;
	else
		y = (tab->player->pos_y / SIZE) * SIZE - 1;
	x = (tab->player->pos_x + (tab->player->pos_y - y) / tan(RAD(a)));
	ya = a > 180.0 ? SIZE : -SIZE;
	xa = (SIZE / tan(RAD(a)));
	a > 180 ? xa = -xa : 0;
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

static t_coord	*vertical_checking(t_wolf *tab, double a)
{
	double		x;
	double		y;
	double		xa;
	double		ya;
	t_coord	*res;

	if (!(res = (t_coord *)malloc(sizeof(t_coord))))
		return (0);
	if (a >= 90.0 && a <= 270.0)
		x = (tab->player->pos_x / SIZE) * SIZE - 1;
	else
		x = (tab->player->pos_x / SIZE + 1) * SIZE;
	y = (tab->player->pos_y + (tab->player->pos_x - x) * tan(RAD(a)));
	xa = (a >= 90.0 && a <= 270.0) ? -SIZE : SIZE;
	ya = (SIZE * tan(RAD(a)));
	a < 90 || a > 270 ? ya = -ya : 0;
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
*/
