/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:16:06 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/06 18:54:35 by nveneros         ###   ########.fr       */
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

	i = 0;
	while (buffer[i] != C_LIMIT || buffer[i] == '\0')
		i++;
	i++;
	return (&buffer[i]);
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

void	check_if_has_start(char **line, char **buffer, char *static_buffer)
{
	char	*copy;
	if (str_contain_c(*buffer, '\n'))
	{
		*buffer = update_new_start_buffer(*buffer);
		*line = check_line(*line, *buffer);
		// MAJ STATIC BUFFER WITH NEW BUFFER BECAUSE 
		// IF YOU HAVE A BUFFER GREATHER THAN THE CONTENT FILE YOU READ THE FILE ONLY ONE TIME
		// static_buffer = *buffer;
		copy = ft_strdup_at_c(*buffer, '\0');
		ft_strcpy(static_buffer, copy);
		free(copy);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	static_buffer[BUFFER_SIZE + 1];
	char		*buffer;
	int			bytes_read;
	int			total_read;

	total_read = 0;
	line = NULL;
	buffer = static_buffer;
	if (read(fd, 0, 0))
		return NULL;
	check_if_has_start(&line, &buffer, static_buffer);
	while (!str_contain_c(buffer, '\n'))
	{
		bytes_read = read(fd, static_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buffer = static_buffer;
		buffer[bytes_read] = 0;
		total_read += bytes_read;
		line = check_line(line, buffer);
	}
	// printf("buffer = %s", buffer);
	return (line);
}

// #include <sys/stat.h>
// #include <fcntl.h>

// int i = 1;

// void	test(int fd)
// {
// 	char	*str;

// 	printf("_________START %d__________\n", i);
// 	str = get_next_line(fd);
// 	printf("Output :%s\n", str);
// 	printf("\n\n\n");
// 	free(str);
// 	i++;
// }

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	test(fd);
// 	test(fd);
// 	test(fd);
// 	test(fd);
// 	test(fd);
// 	return (0);
// }