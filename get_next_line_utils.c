/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:18:13 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/07 16:24:55 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_at_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	str_contain_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_at_c(char *str, char c)
{
	int		i;
	char	*output;

	if (str == NULL)
		return NULL;
	i = 0;
	output = malloc(ft_strlen_at_c(str, c) +1 * sizeof(char));
	while (str[i] && str[i] != c)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

void	ft_strcat_at_c(char *dest, char *src, char c)
{
	int	i;
	int	start;

	i = 0;
	start = ft_strlen(dest);
	while (src[i] && src[i] != c)
	{
		dest[start + i] = src[i];
		i++;
	}
	dest[start + i] = '\0';
}
