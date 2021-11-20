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

//#define BUFFER_SIZE 42

void	send_line(char *buffer, char **buffer_reminder, int l, char	**rtn)
{
	int		i;
	char	*temp;

	i = ft_strchr(buffer, '\n');
	if (i < l)
	{
		if (buffer_reminder)
		{
			temp = ft_substr(buffer, i + 1, (l - i - 1));
			free(*buffer_reminder);
			*buffer_reminder = temp;
		}
		else
			*buffer_reminder = ft_substr(buffer, i + 1, (l - i - 1));
	}
	buffer[i + 1] = 0;
	if (!(*rtn))
		*rtn = ft_strdup(buffer);
	else
	{	
		temp = ft_strjoin(*rtn , buffer);
		free(*rtn);
		*rtn = temp;
	}
}

int	get_line(char *buffer, char **buffer_reminder, int l, char **rtn)
{
	int		i;
	char	*temp;

	buffer[l] = 0;
	*rtn = malloc(1);
	i = ft_strchr(buffer, '\n');
	if (i > -1)
	{
		send_line(buffer, buffer_reminder, l, rtn);
		return (1);
	}
	else
	{
		temp = ft_strjoin(*rtn, buffer);
		free(*rtn);
		*rtn = temp;
		return (0);
	}
	return (0);
}

int	check_reminder(char **buffer_reminder, char **rtn)
{
	int		i;
	char	*temp;

	i = ft_strchr(*buffer_reminder, '\n');
	if (i > -1)
	{
		if (i < BUFFER_SIZE)
		{
			*rtn = ft_substr(*buffer_reminder, 0, i + 1);
			temp = ft_substr(*buffer_reminder, i + 1, (ft_strlen(*buffer_reminder) - i - 1));
			free(*buffer_reminder);
			*buffer_reminder = temp;
			return (1);
		}
		*rtn = *buffer_reminder;
		return (1);
	}
	temp = ft_strjoin(*rtn, *buffer_reminder);
	free(*buffer_reminder);
	if (*rtn)
		free(*rtn);
	*rtn = temp;
	return (0);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*buffer_reminder;
	int			l;
	char	*rtn;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer_reminder)
		if (check_reminder(&buffer_reminder, &rtn))
			return (rtn);
	l = read(fd, buffer, BUFFER_SIZE);
	while (l > 0)
	{
		if (get_line(buffer, &buffer_reminder, l, &rtn))
		{
			return (rtn);
		}
		l = read(fd, buffer, BUFFER_SIZE);
	}
	if (rtn && !l)
	{
		temp = rtn;
		rtn = NULL;
		return (temp);
	}
	free(rtn);
	return (NULL);
}

int	main(void)
{
	int x = open("anas.txt", O_RDWR);
	char *str = get_next_line(x);
	while(str)
	{
		printf("%s", str);
		str = get_next_line(x);
	}
}





// buffer save f rest 
// check new line --> rest if hw found it break the loop 
//
