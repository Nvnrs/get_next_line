/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:16:06 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/07 16:24:49 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define C_LIMIT '\n'

char	*check_line(char *line, char *buffer)
{
	char	*new_line;

	if (buffer == NULL)
		return (NULL);
	if (line == NULL)
		new_line = ft_strdup_at_c(buffer, C_LIMIT);
	else
	{
		new_line = malloc((ft_strlen_at_c(line, C_LIMIT) 
		+ ft_strlen_at_c(buffer, C_LIMIT) + 1));
		if (new_line == NULL)
			return (NULL);
		new_line[0] = '\0';
		ft_strcat_at_c(new_line, line, C_LIMIT);
		ft_strcat_at_c(new_line, buffer, C_LIMIT);
		free(line);
	}
	return (new_line);
}

char	*update_new_start_buffer(char *buffer)
{
	int	i;
	char	*buffer_advanced;

	i = 0;
	while (buffer[i] != C_LIMIT || buffer[i] == '\0')
		i++;
	i++;

	buffer_advanced = ft_strdup_at_c(&buffer[i], '\0');
	return (buffer_advanced);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		/* code */
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	check_if_has_start(char **line, char **buffer)
{
	char	*buffer_advanced;

	if (str_contain_c(*buffer, '\n'))
	{
		buffer_advanced = update_new_start_buffer(*buffer);
		*line = check_line(*line, buffer_advanced);
		free(*buffer);
		*buffer = ft_strdup_at_c(buffer_advanced, '\0');
		free(buffer_advanced);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	static_buffer[BUFFER_SIZE + 1];
	char		*buffer;
	int			bytes_read;

	if (read(fd, 0, 0))
		return NULL;
	line = NULL;
	buffer = ft_strdup_at_c(static_buffer, '\0');
	check_if_has_start(&line, &buffer);
	ft_strcpy(static_buffer, buffer);
	while (!str_contain_c(buffer, '\n'))
	{
		bytes_read = read(fd, static_buffer, BUFFER_SIZE);
		static_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
		{
			free(line);
			free(buffer);
			return (NULL);
		}
		if (buffer != NULL)
			free(buffer);
		buffer = ft_strdup_at_c(static_buffer, '\0');
		line = check_line(line, buffer);
	}
	free(buffer);
	return (line);
}
