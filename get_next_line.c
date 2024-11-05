/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:16:06 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/05 15:52:19 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 10

int	str_contain_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

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
	int		i;
	char	*output;

	i = 0;
	output = malloc(ft_strlen(str) +1 * sizeof(char));
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}


void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	start;

	i = 0;
	start = ft_strlen(dest);
	while (src[i])
	{
		dest[start + i] = src[i];
		i++;
	}
	dest[start + i] = '\0';
}


char	*check_line(char *line, char *buffer)
{
	char	*new_line;

	if (buffer == NULL)
		return (NULL);
	if (line == NULL)
		new_line = ft_strdup(buffer);
	else
	{
		new_line = malloc((ft_strlen(line) + ft_strlen(buffer) + 1));
		if (new_line == NULL)
			return (NULL);
		new_line[0] = '\0';
		ft_strcat(new_line, line);
		ft_strcat(new_line, buffer);
		free(line);
	}
	return (new_line);
}

char *get_next_line(int fd)
{
	char 	*line;
	char	buffer[BUFFER_SIZE + 1];
	int		head_r;
	int		bytes_read;
	int		i;


	bytes_read = 0;
	line = NULL;
	
	while (!str_contain_c(buffer, '\n'))
	{
		line = check_line(line, buffer);
		// printf("LINE :%s\n", line);
		// printf("BUFFER :%s\n", buffer);
		head_r = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = 0;
		bytes_read += head_r;
		i++;
	}

	// treatment if buffer contains \n
	// if true put in line
	if (str_contain_c(buffer, '\n'))
	{
	}
	printf("\nbytes_read : %d\n", bytes_read);
	printf("LINE :%s\n", line);
	return "";
}

#include <sys/stat.h>
#include <fcntl.h>

void	test(int fd)
{
	char	*str;

	str = get_next_line(fd);
	printf("%s\n", str);
	// free(str);
}

int	main(void)
{
	char	*str;
	int fd = open("test.txt", O_RDONLY);
	test(fd);
	return (0);
}