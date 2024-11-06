/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:18:04 by nveneros          #+#    #+#             */
/*   Updated: 2024/11/06 18:18:25 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define C_LIMIT '\n'

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

int		ft_strlen(char *str);
int		ft_strlen_at_c(char *str, char c);
int		str_contain_c(char *str, char c);
char	*ft_strdup_at_c(char *str, char c);
void	ft_strcat_at_c(char *dest, char *src, char c);
char	*get_next_line(int fd);

#endif