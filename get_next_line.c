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

size_t	ft_strlen(const char *s);
#define BUFFER_SIZE 1000000


char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s1[i])
		i++;
	ptr = (char *)malloc(i * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = 0;
	return (ptr);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = -1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ptr = malloc(1);
		ptr[0] = 0;
		return (ptr);
	}
	if (len > (ft_strlen(s) - start))
		ptr = (char *)malloc(ft_strlen(s) - start + 1);
	else
		ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (s[start + ++i] && i < len)
		ptr[i] = s[start + i];
	ptr[i] = 0;
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (dst > src)
	{
		while (len--)
			*(char *)(dst + len) = *(char *)(src + len);
	}
	else if (src > dst)
	{
		while (++i < len)
			*(char *)(dst + i) = *(char *)(src + i);
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i1;
	int		i2;
	char	*ptr;

	if (!s2)
		return (NULL);
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	ptr = (char *)malloc((i1 + i2) * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, s1, i1);
	ft_memmove(ptr + i1, s2, i2);
	ptr[i1 + i2] = 0;
	return (ptr);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static char	*buffer_reminder;
	char	str[BUFFER_SIZE + 1] = {0};
	char	*rtn;
	char *temp;
	int	l;
	int	i = 0;
	rtn = malloc(1);
	if (buffer_reminder)
	{
		i = ft_strchr(buffer_reminder, '\n') ;
		if (i > -1)
		{
			if (i < BUFFER_SIZE)
			{
				free(rtn);
				rtn = ft_substr(buffer_reminder, 0 , i + 1 );

				temp = ft_substr(buffer_reminder, i + 1, (ft_strlen(buffer_reminder) - i - 1));
				free(buffer_reminder);
				buffer_reminder = temp;
				return rtn;
			}
			return (buffer_reminder);
		}
		temp = ft_strjoin(rtn, buffer_reminder);
		free(rtn);
		rtn = temp;
		free(buffer_reminder);
	}
	l = read(fd, str, BUFFER_SIZE);
	if (!l)
	{
		free(rtn);
		return (NULL);
	}
	while (l > 0)
	{
		i = ft_strchr(str, '\n') ;
		if (i > -1)
		{
			if (i < l - 1)
				buffer_reminder = ft_substr(str, i + 1, (l - i - 1));
			str[i + 1] = 0;
			temp = ft_strjoin(rtn, str);
			free(rtn);
			rtn = temp;
			return (rtn);
		}
		else 
		{
			temp = ft_strjoin(rtn, str);
			free(rtn);
			rtn = temp;
		}
		l = read(fd, str, BUFFER_SIZE);
		str[l] = 0;
	}
	if(!l && rtn)
	{
		return rtn;
	}
	free(rtn);
	return (NULL);
}

int	main(void)
{
	int fd = open("anas.txt", O_RDWR);
	char	*str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
}
