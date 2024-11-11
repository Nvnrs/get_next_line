/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:26:03 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/11 15:14:26 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	buffer_skip_first_linebreak(char *buffer_static)
{
	char	*buffer_advanced;
	int		i;

	i = 0;
	buffer_advanced = NULL;
	if (!ft_strlen_at_c(buffer_static, '\0'))
		return ;
	if (!str_contain_c(buffer_static, '\n'))
	{
		ft_strcpy(buffer_static, "");
		return ;
	}
	while (buffer_static[i] != '\n')
		i++;
	buffer_advanced = ft_strdup(&buffer_static[++i]);
	ft_strcpy(buffer_static, buffer_advanced);
	free(buffer_advanced);
}

char	*reduce_str_at_c(char *str, char c)
{
	int		i;
	char	*outptut;

	i = 0;
	outptut = malloc(ft_strlen_at_c(str, c) + 1 * sizeof(char));
	while (str[i] && str[i] != c)
	{
		outptut[i] = str[i];
		i++;
	}
	if (str[i] == c)
	{
		outptut[i] = str[i];
		i++;
	}
	outptut[i] = '\0';
	return (outptut);
}

char	*handle_line(char *line, char *buffer)
{
	char	*buffer_at_breakline;
	char	*new_line;
	int		new_length;

	buffer_at_breakline = reduce_str_at_c(buffer, '\n');
	if (line == NULL)
		new_line = ft_strdup(buffer_at_breakline);
	else
	{
		new_length = ft_strlen_at_c(line, '\0')
			+ ft_strlen_at_c(buffer_at_breakline, '\0');
		new_line = malloc(new_length + 1);
		new_line[0] = '\0';
		ft_strcat(new_line, line);
		ft_strcat(new_line, buffer_at_breakline);
		free(line);
	}
	free(buffer_at_breakline);
	return (new_line);
}

int	read_fd(char **line, char *buffer_static, int fd)
{
	int	bytes_read;

	while (!str_contain_c(buffer_static, '\n'))
	{
		bytes_read = read(fd, buffer_static, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (*line)
				free(*line);
			ft_strcpy(buffer_static, "");
			return (FALSE);
		}
		if (bytes_read == 0)
			break ;
		buffer_static[bytes_read] = 0;
		*line = handle_line(*line, buffer_static);
	}
	return (TRUE);
}

char	*get_next_line(int fd)
{
	static char	buffer_static[1024][BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0)
		return (NULL);
	if (ft_strlen_at_c(buffer_static[fd], '\0'))
		line = handle_line(line, buffer_static[fd]);
	if (!read_fd(&line, buffer_static[fd], fd))
		return (NULL);
	buffer_skip_first_linebreak(buffer_static[fd]);
	return (line);
}
