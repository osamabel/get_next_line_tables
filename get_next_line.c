/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:20:15 by obelkhad          #+#    #+#             */
/*   Updated: 2021/12/19 16:05:00 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	check_end_of_line(char	*buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	return i;
}

// size_t	ft_strlen(char	*str)
// {

// }


// size_t	ft_strlcpy(char	*dst, const char *src, size_t dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize != 0)
// 	{
// 		while (i < dstsize - 1 && src[i])
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (ft_strlen(src));
// }


char	*get_next_line(int fd)
{
	static	char	*lost_chars;
	char			*line;
	char			*temp;
	char			*temp1;
	size_t			check;
	size_t			len;

	if (lost_chars)
		temp1 = lost_chars;
	line = NULL;
	if (lost_chars && check_end_of_line(lost_chars) < strlen(lost_chars))
	{
		check = check_end_of_line(lost_chars);
		len = strlen(lost_chars);
		if ( check < len)
		{
			line = (char *)malloc(sizeof(char) * (check + 2)); // 0 + 2 = 2
			strncpy(line, lost_chars, check + 1); // 0 + 1 = 1
			line[check + 1] = '\0';   // 0 + 2 = 2
			temp = lost_chars + check + 1;
			lost_chars = (char *)malloc(sizeof(char) * (len - check));
			strncpy(lost_chars, temp,len - check);
			free(temp1);
			temp1 = NULL;
		}
		else if (check == len)
		{
			line = (char *)malloc(sizeof(char) * (check + 1));
			strncpy(line, lost_chars, check + 1);
			free(lost_chars);
			lost_chars = NULL;
		}
		return (line);
	}
	return (read_and_store(fd, &lost_chars));
}
