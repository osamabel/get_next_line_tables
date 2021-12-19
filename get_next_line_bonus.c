/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:20:15 by obelkhad          #+#    #+#             */
/*   Updated: 2021/12/19 21:01:25 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

void	creat_line(char	**line, char **lost_chars, char	**last_chars, char **buffer)
{
	size_t	check = check_end_of_line(*buffer);

	if (check < BUFFER_SIZE)
	{
		ft_strjoin(line,lost_chars);
		ft_strsplit(*buffer, last_chars, lost_chars, check);
		ft_strjoin(line,last_chars);
	}
	else
		ft_strjoin(line, buffer);
	if (*buffer)
		free(*buffer);
	buffer = NULL;
}

void	ft_strsplit(char *holder, char **first_part, char **secend_part, size_t position_of_end)
{
	char	*lost;

	if (position_of_end < ft_strlen(holder))
	{
		*first_part = (char *)malloc(sizeof(char) * position_of_end + 2);
		strncpy(*first_part, holder, position_of_end + 1);
		*(*first_part + position_of_end + 1) = '\0';
		lost = (char *)malloc(sizeof(char) * (ft_strlen(holder) - position_of_end));
		strncpy(lost, holder + position_of_end + 1, ft_strlen(holder) - position_of_end);
		if (*lost == '\0')
		{
			free(lost);
			lost = NULL;
		}
		free(*secend_part);
		*secend_part = lost;
	}
	else
	{
		*first_part = (char *)malloc(sizeof(char) * position_of_end + 1);
		strncpy(*first_part, holder, position_of_end + 1);
		free(*secend_part);
		*secend_part = NULL;
	}
}

char	*read_and_store(int	fd, char **line,char **lost_chars)
{
	char	*buffer;
	char	*last_chars;
	int		read_char;
	size_t	check;

	check = BUFFER_SIZE;
	while (check == BUFFER_SIZE)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char <= 0)
		{
			if (buffer)
				free(buffer);
			buffer = NULL;
			return (*line);
		}
		buffer[read_char] = '\0';
		check = check_end_of_line(buffer);
		creat_line(line, lost_chars, &last_chars ,&buffer);
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static	char	*lost_chars[10240];
	char			*line;

	line = NULL;
	if (lost_chars[fd] && check_end_of_line(lost_chars[fd]) <= ft_strlen(lost_chars[fd]))
	{
		ft_strsplit(lost_chars[fd], &line, &lost_chars[fd], check_end_of_line(lost_chars[fd]));
		if (check_end_of_line(line) < ft_strlen(line))
			return (line);
	}
	return (read_and_store(fd, &line, &lost_chars[fd]));
}
