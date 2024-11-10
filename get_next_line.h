/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:18:04 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/10 17:30:27 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define C_LIMIT '\n'
# define TRUE 1
# define FALSE 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_strdup(char *str);
char	*reduce_str_at_c(char *str, char c);
int		ft_strlen_at_c(char *str, char c);
int		str_contain_c(char *str, char c);
void	ft_strcpy(char *dest, char *src);
void	ft_strcat(char *dest, char *src);

#endif