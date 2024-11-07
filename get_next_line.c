/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:26:03 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/07 18:38:44 by nveneros         ###   ########.fr       */
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


char	*ft_strdup(char *str)
{
	char	*output;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	output = malloc(ft_strlen(str) + 1  * sizeof(char));
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

// char	*ft_strcat_realloc(char *str1, char *str2)
// {
	
// }

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

char	*buffer_skip_first_linebreak(char *buffer)
{
	char	*buffer_advanced;
	int		i;

	i = 0;
	buffer_advanced = NULL;
	if (!str_contain_c(buffer, '\n'))
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] != '\n')
		i++;
	buffer_advanced = ft_strdup(&buffer[++i]);
	free(buffer);
	return (buffer_advanced);
}

void	ft_strcat_at_c(char *dest, char *src, char c)
{
	int	i;
	int	start;

	i = 0;
	start = ft_strlen(dest);
	while(src[i] && src[i] != c)
	{
		dest[i + start] = src[i];
		i++;
	}
	dest[i + start] = '\0';
}

char	*handle_line(char *line, char *buffer)
{
	char	*new_line;

	if (line == NULL)
		new_line = ft_strdup(buffer);
	else
	{
		new_line = malloc(ft_strlen(line) + ft_strlen(buffer) + 1);
		new_line[0] = '\0';
		ft_strcat_at_c(new_line, line, '\0');
		ft_strcat_at_c(new_line, buffer, '\0');
		free(line);
	}
	return (new_line);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

// BUFFER IS A COPY OF BUFFER STATIC WITH DYNAMIC ALLOCATION

char	*get_next_line(int fd)
{
	static char buffer_static[BUFFER_SIZE + 1];
	char		*buffer;
	char		*line;
	int			bytes_read;

	bytes_read = 0;
	buffer = NULL;
	line = NULL;

	// CHECK FD VALID
	if (read(fd, 0, 0))
		return (NULL);

	// check if have last buffer static	
	if (ft_strlen(buffer_static))
	{
		// printf("BUFFER STATIC EXISTANT");
		buffer = ft_strdup(buffer_static);
		line = handle_line(line, buffer);
		// printf("LINE :%s\n", line);
	}

	while (!str_contain_c(buffer, '\n'))
	{
		bytes_read = read(fd, buffer_static, BUFFER_SIZE);
		buffer_static[bytes_read] = 0;
		// printf("STATIC :%s\n", buffer_static);
		// printf("LOOP	line :%s\n", line);
		if (bytes_read == 0)
		{
			if (buffer)
				free(buffer);
			if (line)
				free(line);
			return (NULL);
		}
		if (buffer)
			free(buffer);
		buffer = ft_strdup(buffer_static);
		line = handle_line(line, buffer);
	}

	// MAJ BUFFER STATIC
	if (buffer)
	{
		// printf("BUFFER UPDATE FOR NEXT CALL\n");
		buffer = buffer_skip_first_linebreak(buffer);
		ft_strcpy(buffer_static, buffer);
	}
	
	// END
	free(buffer);
	return (line);
}