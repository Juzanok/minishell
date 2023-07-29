/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:26:27 by hrings            #+#    #+#             */
/*   Updated: 2022/06/22 12:52:59 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int		len;
	char	c;

	if (!str)
		return (0);
	len = 0;
	c = *str;
	while (c != '\0')
	{
		len++;
		str++;
		c = *str;
	}
	return (len);
}
