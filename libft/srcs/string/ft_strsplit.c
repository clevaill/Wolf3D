/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:14:09 by akrache           #+#    #+#             */
/*   Updated: 2019/04/26 19:30:22 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static size_t	skip_c(const char *str, size_t i, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

static size_t	words(const char *str, char c)
{
	size_t i;
	size_t nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		i = skip_c(str, i, c);
		while (str[i] && str[i] != c)
			i++;
		nb++;
	}
	if (str[i] == '\0' && str[i - 1] == c)
		return (nb - 1);
	return (nb);
}

static size_t	len(const char *str, size_t i, char c)
{
	size_t ch;

	ch = 0;
	while (str[i] != c && str[i])
	{
		ch++;
		i++;
	}
	return (ch);
}

static void		*free_it(char **str, size_t w)
{
	size_t	stp;

	stp = 0;
	while (stp < w)
		ft_memdel((void **)&str[stp++]);
	ft_memdel((void **)str);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	k;
	size_t	j;
	size_t	l;

	i = 0;
	k = 0;
	if (s == NULL || ((res = (char **)ft_memalloc(sizeof(*res) *
		words((char *)s, c) + 1)) == NULL))
		return (NULL);
	while (i < words(s, c))
	{
		j = 0;
		k = skip_c(s, k, c);
		l = len(s, k, c);
		if ((res[i] = ft_strnew(sizeof(*res) * l + 1)) == NULL)
			return (free_it(res, words(s, c)));
		while (j < l)
			res[i][j++] = s[k++];
		res[i++][j] = '\0';
	}
	res[i] = NULL;
	return (res);
}
