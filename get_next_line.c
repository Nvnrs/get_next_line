/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:26:03 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/10 12:27:52 by nveneros         ###   ########.fr       */
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
	if (str[i] == c)
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


char	*ft_strdup_at_c(char *str, char c)
{
	char	*output;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	output = malloc(ft_strlen_at_c(str, c) + 1  * sizeof(char));
	while (str[i] && str[i] != c)
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

void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	start;

	i = 0;
	start = ft_strlen(dest);
	while(src[i])
	{
		dest[i + start] = src[i];
		i++;
	}
	dest[i + start] = '\0';
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
	return outptut;
	
}

char	*handle_line(char *line, char *buffer)
{
	char	*buffer_at_breakline;
	char	*new_line;
	int		new_length;

	buffer_at_breakline = reduce_str_at_c(buffer, '\n');
	// printf("bufferat_breakline :%s", buffer_at_breakline);
	if (line == NULL)
		new_line = ft_strdup(buffer_at_breakline);
	else
	{
		new_length = ft_strlen(line) + ft_strlen(buffer_at_breakline);
		new_line = malloc(new_length + 1);
		new_line[0] = '\0';
		ft_strcat(new_line, line);
		ft_strcat(new_line, buffer_at_breakline);
		free(line);
	}
	free(buffer_at_breakline);
	return (new_line);
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

// BUFFER IS A COPY OF BUFFER STATIC WITH DYNAMIC ALLOCATION
// BUFFER_TEMP is a copy of buffer without \n
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
	if (fd < 0)
		return (NULL);

	// check if have last buffer static	
	if (ft_strlen(buffer_static))
	{
		// printf("BUFFER STATIC EXISTANT");
		buffer = ft_strdup(buffer_static);
		// printf("BUFFER %s\n", buffer);
		line = handle_line(line, buffer);
		// printf("LINE :%s\n", line);
	}

	while (!str_contain_c(buffer, '\n'))
	{
		bytes_read = read(fd, buffer_static, BUFFER_SIZE);
		buffer_static[bytes_read] = 0;
		// printf("STATIC :%s", buffer_static);
		// printf("LOOP	line :%s\n", line);
		// printf("Bytes READ :%d", bytes_read);
		if (bytes_read == -1)
		{
			if (line)
				free(line);
			if (buffer)
			{
				ft_strcpy(buffer_static, "");
				free(buffer);
			}
			return (NULL);
		}
		if (bytes_read <= 0)
		{
			if (line && ft_strlen(line))
				break;
			else
			{
				if (buffer)
					free(buffer);
				return (line);
			}
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
		// printf("BUFFER %s\n", buffer);
		buffer = buffer_skip_first_linebreak(buffer);
		ft_strcpy(buffer_static, buffer);
		// printf("static %s\n", buffer_static);
	}
	
	// END
	free(buffer);
	return (line);
}