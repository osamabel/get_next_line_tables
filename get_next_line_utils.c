/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:38:41 by obelkhad          #+#    #+#             */
/*   Updated: 2021/12/17 21:36:17 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		len;

	len = strlen(s1);
	p = (char *)malloc((sizeof(char) * (len + 1)));
	if (!p)
		return (0);
	strlcpy(p, s1, len + 1);
	return (p);
}


char	*ft_strjoin(char **first, char **secend)
{
	char	*temp;

	if (!*first)
	{
		*first = strdup(*secend);
		free(*secend);
		return (*secend);
	}
	if (!*secend)
		return (*first);
	if (*first && *secend)
	{
		temp = *first;
		*first = malloc(sizeof(char) * (strlen(*first) + strlen(*secend) + 1));
		strncpy(*first, temp, strlen(temp));
		strncpy(*first + strlen(temp), *secend, strlen(*secend) + 1);
		free(temp);
	}
	return (*first);
}

char	*read_and_store(int	fd, char **lost_chars)
{
	char	*line;
	char	*buffer;
	char	*last_chars;
	int		read_char;
	size_t	check;

	line = NULL;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	check = BUFFER_SIZE;
	while (check == BUFFER_SIZE)
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char <= 0)
		{
			free(buffer);
			return (line);
		}
		buffer[BUFFER_SIZE] = '\0';
		check = check_end_of_line(buffer);
		if (check < BUFFER_SIZE)
			ft_strsplit(buffer, &last_chars, lost_chars, check);
		else
			ft_strjoin(&line, &buffer);
	}
	ft_strjoin(&line, &last_chars);
	free(buffer);
	return (line);
}

void	ft_strsplit(char *buffer, char **last_chars, char **lost_chars, size_t check)
{
	*lost_chars = (char *)malloc(sizeof(char) * (strlen(buffer) - check));
	strncpy(*lost_chars, buffer + check + 1, strlen(buffer) - check);
	if (*lost_chars == '\0')
	{
		free(*lost_chars);
		*lost_chars = NULL;
	}
	if (buffer[check] == '\0')
	{
		*last_chars = (char *)malloc(sizeof(char) * (check + 1));
		strncpy(*last_chars, buffer ,check + 1);
	}
	else
	{
		*last_chars = (char *)malloc(sizeof(char) * (check + 2));
		strncpy(*last_chars, buffer ,check + 1);
		*(*last_chars + check + 2) = '\0';
	}
}