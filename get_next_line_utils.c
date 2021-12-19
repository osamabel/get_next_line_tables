/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:38:41 by obelkhad          #+#    #+#             */
/*   Updated: 2021/12/19 20:15:38 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	check_end_of_line(char	*buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	return (i);
}

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char **line, char **secend)
{
	char	*temp;

	if (!*line && *secend)
	{
		*line = (char *)malloc(sizeof(char) * (ft_strlen(*secend) + 1));
		ft_strncpy(*line, *secend, ft_strlen(*secend) + 1);
		free(*secend);
		*secend = NULL;
		return (*line);
	}
	if (*line && *secend)
	{
		temp = *line;
		*line = malloc(sizeof(char) * (ft_strlen(*line) + ft_strlen(*secend) + 1));
		ft_strncpy(*line, temp, ft_strlen(temp));
		ft_strncpy(*line + ft_strlen(temp), *secend, ft_strlen(*secend) + 1);
		free(*secend);
		*secend = NULL;
		free(temp);
	}
	return (*line);
}

void	ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < len)
	{
		*(dest + i) = '\0';
		i++;
	}
}


