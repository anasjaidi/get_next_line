/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:06:41 by ajaidi            #+#    #+#             */
/*   Updated: 2021/11/17 01:48:06 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 42

void	get_line(char *buffer)
{

}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buffer_reminder;
	int			l;

	if (fd < 0)
		return (NULL);
	l = read(fd, buffer, BUFFER_SIZE);
	while (l > 0)
	{
		get_line(buffer);
		l = read(fd, buffer, BUFFER_SIZE);
	}
}
