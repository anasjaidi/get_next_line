/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:06:41 by ajaidi            #+#    #+#             */
/*   Updated: 2021/11/15 06:53:12 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);
#define BUFFER_SIZE 42 

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
	int	x;
	int	i;
	char	*str;
	static char	*rtnn;
	char	*rtn;
	static char	*rttn;
	rttn = malloc(1);
	str = malloc(BUFFER_SIZE + 1);
	str[BUFFER_SIZE + 1] = 0;
	rtn = malloc(1);
	rtnn  = malloc(1);
	x = read(fd, str, BUFFER_SIZE);
	while (x)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == '\n')
			{
				if(i < BUFFER_SIZE)
				{
					rttn = ft_strdup(rtnn);
					rtnn = ft_substr(str, i + 1 , (BUFFER_SIZE - i - 1));
					printf("this is rtnn	%s\n", rtnn);
				}
				str[i + 1] = 0;
				rttn = ft_strjoin(rttn, str);
				return rttn;
			}
			if (!str[i + 1])
			{
				rtnn = ft_strjoin(rtnn, str);
			}
			i++;
		}
		x = read(fd, str, BUFFER_SIZE);
	}
	i = 0;
	if (!x)
	{
		while(rtnn[i])
		{
			if (rtnn[i] == '\n')
			{
				return rtnn;
			}
			i++;
		}

	}
	return ("anas");
}

int	main(void)
{
	int fd = open("anas.txt", O_RDWR);
	char	*str = get_next_line(fd);
	printf("%s\n",str);
	str = get_next_line(fd);
	printf("%s\n",str);
	str = get_next_line(fd);
	printf("%s\n",str);
}
