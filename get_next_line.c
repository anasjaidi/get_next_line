/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:40:22 by ajaidi            #+#    #+#             */
/*   Updated: 2021/11/22 01:50:41 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	send_line(char *buffer, char **buffer_reminder, int l, char	**rtn)
{
	int		i;
	char	*temp;

	i = ft_strchr(buffer, '\n');
	if (i < l)
	{
		if (*buffer_reminder)
		{
			temp = ft_substr(buffer, i + 1, (l - i - 1));
			free(*buffer_reminder);
			*buffer_reminder = temp;
		}
		else if (buffer[i + 1] != 0)
			*buffer_reminder = ft_substr(buffer, i + 1, (l - i - 1));
	}
	buffer[i + 1] = 0;
	if (!(*rtn))
		*rtn = ft_strdup(buffer);
	else
	{	
		temp = ft_strjoin(*rtn, buffer);
		free(*rtn);
		*rtn = temp;
	}
}

int	get_line(char *buffer, char **buffer_reminder, int l, char **rtn)
{
	int		i;
	char	*temp;

	buffer[l] = 0;
	i = ft_strchr(buffer, '\n');
	if (i > -1)
	{
		send_line(buffer, buffer_reminder, l, rtn);
		return (1);
	}
	else
	{
		if (!*rtn)
			*rtn = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(*rtn, buffer);
			free(*rtn);
			*rtn = temp;
		}
		return (0);
	}
	return (0);
}

int	check_reminder(char **buffer_reminder, char **rtn)
{
	int		i;
	char	*temp;
	int		size;

	size = ft_strlen(*buffer_reminder);
	i = ft_strchr(*buffer_reminder, '\n');
	if (i > -1)
	{
		if (i < size - 1)
		{
			*rtn = ft_substr(*buffer_reminder, 0, i + 1);
			temp = ft_substr(*buffer_reminder, i + 1, (size - i - 1));
			free(*buffer_reminder);
			*buffer_reminder = temp;
			return (1);
		}
		*rtn = *buffer_reminder;
		*buffer_reminder = NULL;
		return (1);
	}
	temp = ft_strjoin("", *buffer_reminder);
	free(*buffer_reminder);
	*buffer_reminder = NULL;
	*rtn = temp;
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buffer_reminder;
	int			l;
	char		*rtn;

	rtn = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer_reminder && check_reminder(&buffer_reminder, &rtn))
		return (rtn);
	buffer = malloc(BUFFER_SIZE + 1);
	l = read(fd, buffer, BUFFER_SIZE);
	while (l > 0)
	{
		if (get_line(buffer, &buffer_reminder, l, &rtn))
		{
			free(buffer);
			return (rtn);
		}
		l = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (rtn);
}
