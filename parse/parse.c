/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:59:29 by akrache           #+#    #+#             */
/*   Updated: 2019/04/15 19:35:36 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void		*ft_free(char *str)
{
	free(str);
	return (0);
}

static char			*ft_readfile(char *arg)
{
	char	*tmp;
	int		i;
	char	*file;
	char	buf[BUFF_SIZE + 1];
	int		fd;

	if ((fd = open(arg, O_RDONLY)) == -1)
		return (0);
	i = (int)read(fd, buf, BUFF_SIZE);
	if (i == -1)
		return (0);
	buf[i] = '\0';
	if (!(file = ft_strdup(buf)))
		return (0);
	while (file && (i = (int)read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		tmp = file;
		file = ft_strjoin(file, buf);
		free(tmp);
	}
	close(fd);
	return (file ? file : ft_free(file));
}

void	quick_check(char *file, int *x, int *y)
{
	int i;

	i = 0;
	while (file[i] && file[i] != '\n')
	{
		file[i] != ' ' ? (*x)++ : 0;
		i++;
	}
	while (file[i])
	{
		file[i] == '\n' ? (*y)++ : 0;
		i++;
	}
	file[i - 1] != '\n' ? (*y)++ : 0;
}

char	**quick_parse(char *arg, int *x, int *y)
{
	char	*file;
	char	**res;
	int		i;
	int		j;
	int		k;

	if (!(file = ft_readfile(arg)))
		return (0);
	quick_check(file, x, y);
	res = (char **)malloc(sizeof(char *) * (*y) + 1);
	res[(*y)] = 0;
	i = -1;
	while (++i < (*y))
	{
		res[i] = malloc(sizeof(char) * (*x) + 1);
		res[i][(*x)] = 0;
	}
	i = 0;
	j = 0;
	k = 0;
	while(file[i])
	{
		if (file[i] == '\n')
		{
			j++;
			k = 0;
		}
		if (ft_isdigit((char)file[i]))
		{
			res[j][k] = file[i];
			k++;
		}
		i++;
	}
	free(file);
	return (res);
}

t_block	*block_init(char type, char texture)
{
	t_block *res;

	if(!(res = (t_block *)malloc(sizeof(t_block))))
		return (0);
	res->type = type;
	res->texture = texture;
	return (res);
}

t_block	***quick_grid(char **tab, int x, int y)
{
	int i;
	int j;
	t_block	***res;

	i = 0;
	res = (t_block ***)malloc(sizeof(t_block **) * (y + 1));
	res[y] = 0;
	while(tab[i])
	{
		j = 0;
		res[i] = (t_block **)malloc(sizeof(t_block *) * (x + 1));
		res[i][x] = 0;
		while(tab[i][j])
		{
			res[i][j] = block_init(tab[i][j], 0);
			j++;
		}
		i++;
	}
	return (res);
}

t_map	*map_init(char *arg)
{
	t_map	*map;
	char	**tmp;
	int		x;
	int		y;
	int		i;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	x = 0;
	y = 0;
	tmp = quick_parse(arg, &x, &y);
	map->width = x;
	map->height = y;
	map->grid = quick_grid(tmp, x, y);
	i = -1;
	while(tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (map);
}
