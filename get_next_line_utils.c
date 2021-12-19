/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:38:41 by obelkhad          #+#    #+#             */
/*   Updated: 2021/12/19 16:03:56 by obelkhad         ###   ########.fr       */
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


char	*ft_strjoin(char **line, char **secend) // lost char = 13145465413 , line
{
	char	*temp;

	if (!*line && *secend) //NULL && "##"
	{
		*line = strdup(*secend);
		free(*secend);
		*secend = NULL;
		return (*line);
	}
	if (*line && *secend)
	{
		temp = *line;
		*line = malloc(sizeof(char) * (strlen(*line) + strlen(*secend) + 1));
		strncpy(*line, temp, strlen(temp));
		strncpy(*line + strlen(temp), *secend, strlen(*secend) + 1);
		free(*secend);
		*secend = NULL;
		free(temp);
	}
	return (*line);
}

char	*read_and_store(int	fd, char **lost_chars)
{
	char	*line;
	char	*buffer;//buffer[BUFFER_SIZE + 1];
	char	*last_chars;
	int		read_char;
	size_t	check;

	line = NULL;
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
			if (!*lost_chars)
				ft_strjoin(&line,lost_chars);
			return (line);
		}
		buffer[read_char] = '\0';
		check = check_end_of_line(buffer);
		if (check < BUFFER_SIZE)  //  check < strlen(buffer)
		{
			//if (*lost_chars)
			ft_strjoin(&line,lost_chars);
			ft_strsplit(buffer, &last_chars, lost_chars, check);
			ft_strjoin(&line,&last_chars);
		}
		else
			ft_strjoin(&line, &buffer);
	}
	//ft_strjoin(&line, &last_chars);
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (line);
}

void	ft_strsplit(char *buffer, char **last_chars, char **lost_chars, size_t check)
{
	// buffer = \n , \0   [0 , 1]
	// char	*line;
	// line = malloc(sizeof(char) * 2);
	// line[0] = 'M';
	// line[1] = 'H';

	*lost_chars = (char *)malloc(sizeof(char) * (strlen(buffer) - check)); // 42 - 0 = 42
	strncpy(*lost_chars, buffer + check + 1, strlen(buffer) - check);  // 42
	//strncpy(*lost_chars, line + check + 1, strlen(buffer) - check);  // 0 + 1
	if (*(*lost_chars) == '\0')
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
		*last_chars = (char *)malloc(sizeof(char) * (check + 2)); //41 + 2 = 45
		strncpy(*last_chars, buffer ,check + 1);                  //41 + 1 = 44
		*(*last_chars + check + 1) = '\0';                        //41 + 
	}
}