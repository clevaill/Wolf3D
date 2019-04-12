/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:42:36 by akrache           #+#    #+#             */
/*   Updated: 2019/03/27 16:31:28 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tmp;

	tmp = b;
	while (len != 0)
	{
		*tmp = (unsigned char)c;
		tmp++;
		len--;
	}
	return (b);
}
