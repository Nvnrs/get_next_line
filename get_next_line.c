/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:16:06 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/06 16:50:13 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 10
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
		new_line = malloc((ft_strlen(line) + ft_strlen(buffer) + 1));
		if (new_line == NULL)
			return (NULL);
		new_line[0] = '\0';
		ft_strcat_at_c(new_line, line, C_LIMIT);
		ft_strcat_at_c(new_line, buffer, C_LIMIT);
		free(line);
	}
	return (new_line);
}

char	*update_new_start_buffer(char *line, char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] != C_LIMIT || buffer[i] == '\0')
		i++;
	i++;
	return (&buffer[i]);
}

char *get_next_line(int fd)
{
	char 		*line;
	static char	static_buffer[BUFFER_SIZE + 1];
	char		*buffer;
	int			bytes_read;
	int			total_read;

	total_read = 0;
	line = NULL;
	buffer = static_buffer;

	// check start if buffer contain \n
	if(str_contain_c(buffer, '\n'))
	{
		printf("BEFORE update BUFF :***%s***\n", buffer);
		buffer = update_new_start_buffer(line, buffer);
		printf("NEW_START BUFF :***%s***\n", buffer);
		line = check_line(line, buffer);
		printf("Output :%s\n", line);
	}
	
	while (!str_contain_c(buffer, '\n'))
	{
		bytes_read = read(fd, static_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		buffer = static_buffer;
		buffer[bytes_read] = 0;
		total_read += bytes_read;
		line = check_line(line, buffer);
		// printf("BUFFER :***%s***\n", buffer);
		// printf("-> LINE :%s\n\n", line);
	}
	printf("\nBUFFER end :***%s***\n", buffer);
	printf("total_read : %d\n", total_read);
	return (line);
}

#include <sys/stat.h>
#include <fcntl.h>

int i = 1;
void	test(int fd)
{
	char	*str;

	printf("_________START %d__________\n", i);
	str = get_next_line(fd);
	printf("Output :%s\n", str);
	printf("\n\n\n");
	free(str);
	i++;
}

int	main(void)
{
	char	*str;
	int fd = open("test.txt", O_RDONLY);
	test(0);
	return (0);
}