/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 13:52:41 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/12/07 12:46:00 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *src, size_t len)
{
	char	*dst;
	size_t	i;
	
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (free(src), NULL);
	i = 0;
	while (src[i] && i < (len))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, unsigned int i, unsigned int j)
{
	char			*buffer;

	buffer = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buffer)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	if (s1)
	{
		while (s1[i])
		{
			buffer[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[j])
	{
		buffer[i] = s2[j];
		i++;
		j++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_strchr(char *s, char c)
{
	int i;

	if (!s)
		return (NULL);
	i = 0;
	while (s && c != s[i])
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return (s + i);
}
