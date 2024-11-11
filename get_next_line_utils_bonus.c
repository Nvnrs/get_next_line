/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:05:43 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/11 14:09:00 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_at_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c && c != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*output;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	output = malloc((ft_strlen_at_c(str, '\0') + 1) * sizeof(char));
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

int	str_contain_c(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	start;

	i = 0;
	start = ft_strlen_at_c(dest, '\0');
	while (src[i])
	{
		dest[i + start] = src[i];
		i++;
	}
	dest[i + start] = '\0';
}
